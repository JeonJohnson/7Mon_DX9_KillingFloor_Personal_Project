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
	//1. cpu클럭 측정
	QueryPerformanceFrequency(&m_CpuTick);

	//2. 시작시점 주파수 측정
	QueryPerformanceCounter(&m_BeginTime);
	QueryPerformanceCounter(&m_EndTime);
}

void TimeManager::Time_Update()
{
	//혹시 모르니 cpu 클럭 재측정
	QueryPerformanceFrequency(&m_CpuTick);
	//끝 시점 주파수 측정
	QueryPerformanceCounter(&m_EndTime);

	//계산하기
	//(끝지점-시작지점)/씨퓨클럭
	m_fDeltaTime = float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CpuTick.QuadPart;

	//계산하고 나면 다시
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

