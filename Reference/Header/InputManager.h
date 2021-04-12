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

	//0x80 �̶� &���� ��Ʈ ������ ������ �������
	//0�̸� Ű ���� = false
	//1�̸� ���� = true
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
	//LONG    lX; -> ���콺 x ��ǥ ��ȭ��
	//LONG    lY; -> ���콺 y ��ǥ ��ȭ��
	//LONG    lZ; -> ���콺 �� ��ȭ��
	//BYTE    rgbButtons[4]; 
	//0->��Ŭ�� 
	//1->��Ŭ��
	//2->�ٹ�ư
	//3->Ȯ���ư
	
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