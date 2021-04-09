#include "..\Header\InputManager.h"


Implement_Singleton(InputManager)

InputManager::InputManager() 
	//:m_dwKey(0), m_dwKeyDown(0), m_dwKeyUp(0)
{
}


InputManager::~InputManager()
{
	Release();
}

void InputManager::Initialize(HINSTANCE hInst, HWND hWnd)
{

	//DInput8 Device Create
	if (FAILED(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDInput8_SDK,
		NULL)))
	{
		assert(L"DInput8 Device Create Failed" && m_pDInput8_SDK);
	}


	if (FAILED(Keyboard_Create(hWnd)))
	{
		assert(0 && L"Keyboard Create is failed");
	}

	if (FAILED(Mouse_Create(hWnd)))
	{
		assert(0 && L"Mouse Create is failed");
	}



}

void InputManager::Update()
{

}

void InputManager::Release()
{
	Safe_Release(m_pDInput8_Keyboard);
	Safe_Release(m_pDInput8_Mouse);
	Safe_Release(m_pDInput8_SDK);
}

HRESULT InputManager::Keyboard_Create(HWND hWnd)
{
	//Ű���� ��ü ����
	if (FAILED(m_pDInput8_SDK->CreateDevice(GUID_SysKeyboard,
		&m_pDInput8_Keyboard, nullptr)))
	{
		return E_FAIL;
	}

	//Ű���� ��ü�� �İ�ü���� ����.
	if (FAILED(m_pDInput8_Keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//��ġ�� ���� ������ ����.
	if (FAILED(m_pDInput8_Keyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		//=> Ŭ���̾�Ʈ�� ��Ŀ�� �Ǿ��������� �Է¹޵���.
		return E_FAIL;
	}

	//��ġ�� ���� access ������ �޾ƿ�.
	if (FAILED(m_pDInput8_Keyboard->Acquire()))
	{
		return E_FAIL;
	}

	//Ű������ �Է� ���¸� ������ ���� �Ѱ���
	if (FAILED(m_pDInput8_Keyboard->GetDeviceState(256, m_scKeyboard_State)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT InputManager::Mouse_Create(HWND hWnd)
{
	if (FAILED(m_pDInput8_SDK->CreateDevice(GUID_SysMouse,
		&m_pDInput8_Mouse, nullptr)))
	{
		return E_FAIL;
	}

	//���콺 ��ü�� �İ�ü���� ����.
	if (FAILED(m_pDInput8_Mouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//��ġ�� ���� ������ ����.
	if (FAILED(m_pDInput8_Mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		//=> Ŭ���̾�Ʈ�� ��Ŀ�� �Ǿ��������� �Է¹޵���.
		return E_FAIL;
	}

	//��ġ�� ���� access ������ �޾ƿ�.
	if (FAILED(m_pDInput8_Mouse->Acquire()))
	{
		return E_FAIL;
	}

	//���콺�� �Է� ���¸� ������ ����ü
	if (FAILED(m_pDInput8_Mouse->GetDeviceState(sizeof(m_tMouse_State), &m_tMouse_State)))
	{
		return E_FAIL;
	}


	return S_OK;

}

//bool InputManager::GetKeyUp(const DWORD & _dwKey)
//{
//	if (m_dwKey & _dwKey)
//	{
//		m_dwKeyUp |= _dwKey;
//		return false;
//	}
//	else if (m_dwKeyUp & _dwKey)
//	{
//		m_dwKeyUp ^= _dwKey;
//		return true;
//	}
//	return false;
//}
//
//bool InputManager::GetKeyDown(const DWORD & _dwKey)
//{
//	if ((m_dwKey & _dwKey) && !(m_dwKeyDown & _dwKey))
//	{
//		m_dwKeyDown |= _dwKey;
//		return true;
//	}
//	else if (!(m_dwKey & _dwKey) && (m_dwKeyDown & _dwKey))
//	{
//		m_dwKeyDown ^= _dwKey;
//		return false;
//	}
//	return false;
//}
//
//bool InputManager::GetKeyPress(const DWORD & _dwKey)
//{
//	if (m_dwKey & _dwKey)
//	{
//		return true;
//	}
//	return false;
//}

