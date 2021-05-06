#pragma once

#ifndef _DEBUG_MANAGER_H_
#define _DEBUG_MANAGER_H_

#include "Engine_Include.h"


class DLL_STATE DebugManager
{
	Declare_Singleton(DebugManager)
	//일단 트랜스폼까지 적용되는거 확인하고
	//윈도우창 2개 띄운다음에
	//Font 객체로 텍스트 띄워지는거 확인되면 그떄 만들어보자.

public:
	DebugManager();
	~DebugManager();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

public: /* func */


	void DebugLog(const wstring& _script);

	void DebugLog_Reset();
public: /* Get */

public: /* Set */

private:
	LPDIRECT3DDEVICE9		m_pDx9_Device_Debug = nullptr;
	LPD3DXFONT				m_pDx9_Font = nullptr;

	RECT					m_tRect = { 0,0,0,0 };
	D3DXFONT_DESCW			m_tFontDesc;
	wstring					m_szLog;

};

#endif //_DEBUG_MANAGER_H_