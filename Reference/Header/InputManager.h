#pragma once

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "Engine_Include.h"



class DLL_STATE InputManager
{
	Declare_Singleton(InputManager)

private:
	InputManager();
	~InputManager();

public:
	void Initialize(HINSTANCE hInst, HWND hWnd);
	void Update();
	void Release();

public:
	//bool	GetKeyUp(const DWORD & _dwKey);
	//bool	GetKeyDown(const DWORD & _dwKey);
	//bool	GetKeyPress(const DWORD & _dwKey);

public:
	HRESULT		Keyboard_Create(HWND hWnd);
	HRESULT		Mouse_Create(HWND hWnd);

	
private:
	LPDIRECTINPUT8				m_pDInput8_SDK	= nullptr;
	
	LPDIRECTINPUTDEVICE8		m_pDInput8_Keyboard = nullptr;
	signed char					m_scKeyboard_State[256];

	LPDIRECTINPUTDEVICE8		m_pDInput8_Mouse	= nullptr;
	DIMOUSESTATE				m_tMouse_State;
	
	//DWORD m_dwKey;
	//DWORD m_dwKeyUp;
	//DWORD m_dwKeyDown;

	
};

#endif //_INPUT_MANAGER_H_