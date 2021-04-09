#include "..\Header\TimeManager.h"

Implement_Singleton(TimeManager)

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
	
}

void TimeManager::Time_Init()
{
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_BeginTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_EndTime, sizeof(LARGE_INTEGER));

	m_fDeltaTime = 0.f;
	//1. cpuŬ�� ����
	QueryPerformanceFrequency(&m_CpuTick);

	//2. ���۽��� ���ļ� ����
	QueryPerformanceCounter(&m_BeginTime);
	QueryPerformanceCounter(&m_EndTime);
}

void TimeManager::Time_Update()
{
	//Ȥ�� �𸣴� cpu Ŭ�� ������
	QueryPerformanceFrequency(&m_CpuTick);
	//�� ���� ���ļ� ����
	QueryPerformanceCounter(&m_EndTime);

	//����ϱ�
	//(������-��������)/��ǻŬ��
	m_fDeltaTime = float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CpuTick.QuadPart;

	//����ϰ� ���� �ٽ�
	m_BeginTime = m_EndTime;

	FPS_Update();
}

void TimeManager::FPS_Update()
{
	m_fFPS_Time += m_fDeltaTime;

	++m_iFPS;

	if (m_fFPS_Time >= 1.f)
	{
		m_iFPS_Render = m_iFPS;
		m_fFPS_Time = 0.f;
		m_iFPS = 0;
		return;
	}

}

int TimeManager::Get_FPS() const
{
	return m_iFPS_Render;
}

