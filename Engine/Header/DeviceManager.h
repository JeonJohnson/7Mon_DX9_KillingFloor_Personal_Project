#pragma once
#ifndef _DEVICE_MANAGER_H_
#define _DEVICE_MANAGER_H_

#include "Engine_Include.h"

class DeviceManager
{

	Declare_Singleton(DeviceManager)

public:
	DeviceManager();
	~DeviceManager();

public:
	void Initialize(HWND _hWnd, UINT _wincx, UINT _wincy, bool _windowMode);
	void Release();
	
	
public:
	HRESULT	Ready_D3D9(HWND _hWnd, UINT _wincx, UINT _wincy, bool _windowMode);

public:
	LPDIRECT3DDEVICE9		Get_D3D9_Device() const;

private:
	LPDIRECT3D9				m_pD3D9_SDK = nullptr;
	LPDIRECT3DDEVICE9		m_pD3D9_Device = nullptr;


	//LPD3DXLINE				m_pD3D9_Line = nullptr;
	//따로 라인매니저에서 해주기.
};


#endif