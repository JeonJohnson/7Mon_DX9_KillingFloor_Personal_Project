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

	//0x80 이랑 &으로 비트 연산을 했을때 결과값이
	//0이면 키 때짐 = false
	//1이면 눌림 = true
	bool	GetKeyUp(const BYTE& _KeyVal);
	bool	GetKeyDown(const BYTE& _KeyVal);
	bool	GetKeyPress(const BYTE& _KeyVal);

public:
	HRESULT		Keyboard_Create(HWND hWnd);
	HRESULT		Mouse_Create(HWND hWnd);

	void		Check_WindowFocus();

	
	
private:
	LPDIRECTINPUT8				m_pDInput8_SDK	= nullptr;
	
	LPDIRECTINPUTDEVICE8		m_pDInput8_Keyboard = nullptr;
	BYTE*						m_ucKeyboard_CurState;
	BYTE*						m_ucKeyboard_PreState;

	LPDIRECTINPUTDEVICE8		m_pDInput8_Mouse	= nullptr;
	DIMOUSESTATE				m_tMouse_State;
	//LONG    lX; -> 마우스 x 좌표 변화량
	//LONG    lY; -> 마우스 y 좌표 변화량
	//LONG    lZ; -> 마우스 휠 변화량
	//BYTE    rgbButtons[4]; 
	//0->좌클릭 
	//1->우클릭
	//2->휠버튼
	//3->확장버튼
	
	//DWORD m_dwKey;
	//DWORD m_dwKeyUp;
	//DWORD m_dwKeyDown;

	
};

#endif //_INPUT_MANAGER_H_

//bool Update(void)
//{
//	//if (!p_KeyboardDevice)
//	//{
//	//	if (FAILED(p_Object->CreateDevice(GUID_SysKeyboard, &p_KeyboardDevice, 0))) return false;
//	//	if (FAILED(p_KeyboardDevice->SetDataFormat(&c_dfDIKeyboard))) return false;
//	//	if (FAILED(p_KeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) return false;
//	//	if (FAILED(p_KeyboardDevice->Acquire())) return false;
//	//}
//
//	unsigned char *tempKeyStates = p_PrevKeyStates;
//	p_PrevKeyStates = p_CurKeyStates;
//	p_CurKeyStates = tempKeyStates;
//
//	if (FAILED(p_KeyboardDevice->GetDeviceState(256, p_CurKeyStates)))
//	{
//		if (FAILED(p_KeyboardDevice->Acquire())) return false;
//	}
//
//	return true;
//};