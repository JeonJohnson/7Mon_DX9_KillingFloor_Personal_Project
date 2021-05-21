#include "..\Header\DebugManager.h"
#include "DeviceManager.h"

Implement_Singleton(DebugManager);

DebugManager::DebugManager()
{


	
}


DebugManager::~DebugManager()
{
	Safe_Release(m_pDx9_Font);
}

void DebugManager::Initialize()
{
#ifdef _DEBUG
	m_pDx9_Device_Debug = DeviceManager::Get_Instance()->Get_DX9_Device_DEBUG();

	ZeroMemory(&m_tFontDesc, sizeof(D3DXFONT_DESCW));

	m_tFontDesc.Height = 14;
	m_tFontDesc.Weight = FW_BOLD;
	m_tFontDesc.CharSet = HANGUL_CHARSET;

	Vector2 temp = DeviceManager::Get_Instance()->Get_WindowSize_DEBUG();
	m_tRect = { 0,0,(LONG)temp.x, (LONG)temp.y };

	D3DXCreateFontIndirect(m_pDx9_Device_Debug, &m_tFontDesc, &m_pDx9_Font);

	assert(L"Debuging Font is nullptr" && m_pDx9_Font);
#endif //_DEBUG
}

void DebugManager::Update()
{
}

void DebugManager::Render()
{

#ifdef _DEBUG
	m_pDx9_Font->DrawTextW(
		nullptr,
		m_szLog.c_str(),
		-1,
		&m_tRect,
		DT_LEFT | DT_NOCLIP,
		D3DCOLOR_RGBA(0, 255, 0, 255));
#endif //_DEBUG
}

void DebugManager::Release()
{
}

void DebugManager::DebugLog(const wstring & _script)
{
#ifdef _DEBUG
	m_szLog += L"\n------------------------------------------\n" + _script;
#endif //_DEBUG
}

void DebugManager::DebugLog_Reset()
{
#ifdef _DEBUG
	m_szLog = L"Debug Logs";
#endif //_DEBUG
}
