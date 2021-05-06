#pragma once

#ifndef _DEBUG_MANAGER_H_
#define _DEBUG_MANAGER_H_

#include "Engine_Include.h"


class DLL_STATE DebugManager
{
	Declare_Singleton(DebugManager)
	//�ϴ� Ʈ���������� ����Ǵ°� Ȯ���ϰ�
	//������â 2�� ��������
	//Font ��ü�� �ؽ�Ʈ ������°� Ȯ�εǸ� �׋� ������.

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