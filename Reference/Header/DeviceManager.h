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
	
public: /* Direct Device */
	HRESULT	Ready_DX9_Device(HWND _hWnd, UINT _wincx, UINT _wincy, bool _windowMode);
	

public: /* Get */
	LPDIRECT3DDEVICE9		Get_DX9_Device() const;
	const Vector2&			Get_WindowSize() const;


private: /* Dx9 Coms */
	LPDIRECT3D9				m_pDX9_SDK = nullptr;

	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

public: /* vari */
	Vector2 m_vWindowSize;


#ifdef _DEBUG
public:
	HRESULT Ready_DX9_Device_DEBUG(HWND _hWnd, UINT _wincx, UINT _wincy);
	LPDIRECT3DDEVICE9		Get_DX9_Device_DEBUG() const;

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device_DEBUG = nullptr;
#endif //_DEBUG

	//LPD3DXLINE				m_pD3D9_Line = nullptr;
	//따로 라인매니저에서 해주기.
};


#endif //_DEVICE_MANAGER_H_