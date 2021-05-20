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
	HRESULT	Ready_DX9_SpriteCom();

public: /* Get */
	LPDIRECT3DDEVICE9		Get_DX9_Device() const;
	LPD3DXSPRITE			Get_DX9_Sprite() const;
	const Vector2&			Get_WindowSize() const;
	HWND					Get_HWND();

private: /* Dx9 Coms */
	LPDIRECT3D9				m_pDX9_SDK = nullptr;
	
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;
	LPD3DXSPRITE			m_pDX9_Sprite = nullptr;
	HWND					m_hWnd = nullptr;
	

public: /* vari */
	Vector2 m_vWindowSize;


#ifdef _DEBUG
public:
	HRESULT Ready_DX9_Device_DEBUG(HWND _hWnd, UINT _wincx, UINT _wincy);
	LPDIRECT3DDEVICE9		Get_DX9_Device_DEBUG() const;
	const Vector2&			Get_WindowSize_DEBUG() const;

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device_DEBUG = nullptr;
	Vector2					m_vWindowSize_DEBUG;
#endif //_DEBUG

	//LPD3DXLINE				m_pD3D9_Line = nullptr;
	//���� ���θŴ������� ���ֱ�.
};


#endif //_DEVICE_MANAGER_H_