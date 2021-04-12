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
	//전 프레임이랑 비교하기 위해서 
	unsigned char*	Keyboard_TempState = m_ucKeyboard_PreState;
	m_ucKeyboard_PreState = m_ucKeyboard_CurState;
	m_ucKeyboard_CurState = Keyboard_TempState;

	//BYTE* Mouse_TempState = m_tMouseButton_PreState;
	//m_tMouse_State.rgbButtons = 

	Check_WindowFocus();


	////키보드의 입력 상태를 저장할 변수 넘겨줌
	//m_pDInput8_Keyboard->GetDeviceState(256, m_ucKeyboard_CurState);
	////마우스의 입력 상태를 저장할 구조체
	//m_pDInput8_Mouse->GetDeviceState(sizeof(m_tMouse_State), &m_tMouse_State);
	
}

void InputManager::Release()
{
	Safe_Delete(m_ucKeyboard_CurState);
	Safe_Delete(m_ucKeyboard_PreState);

	m_pDInput8_Keyboard->Unacquire();
	Safe_Release(m_pDInput8_Keyboard);
	
	//Safe_Delete(m_tMouseButton_PreState);
	m_pDInput8_Mouse->Unacquire();
	Safe_Release(m_pDInput8_Mouse);

	Safe_Release(m_pDInput8_SDK);
}

HRESULT InputManager::Keyboard_Create(HWND hWnd)
{
	//키보드 객체 생성
	if (FAILED(m_pDInput8_SDK->CreateDevice(GUID_SysKeyboard,
		&m_pDInput8_Keyboard, nullptr)))
	{
		return E_FAIL;
	}

	//키보드 객체를 컴객체에게 전달.
	if (FAILED(m_pDInput8_Keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//장치에 대한 독점권 설정.
	if (FAILED(m_pDInput8_Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		//=> 클라이언트에 포커싱 되어있을때만 입력받도록.
		return E_FAIL;
	}

	//장치에 대한 access 버전을 받아옴.
	if (FAILED(m_pDInput8_Keyboard->Acquire()))
	{
		return E_FAIL;
	}

	m_ucKeyboard_CurState = new BYTE[256];
	m_ucKeyboard_PreState = new BYTE[256];

	ZeroMemory(m_ucKeyboard_PreState, 256);
	ZeroMemory(m_ucKeyboard_CurState, 256);

	return S_OK;
}

HRESULT InputManager::Mouse_Create(HWND hWnd)
{
	if (FAILED(m_pDInput8_SDK->CreateDevice(GUID_SysMouse,
		&m_pDInput8_Mouse, nullptr)))
	{
		return E_FAIL;
	}

	//마우스 객체를 컴객체에게 전달.
	if (FAILED(m_pDInput8_Mouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//장치에 대한 독점권 설정.
	if (FAILED(m_pDInput8_Mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		//=> 클라이언트에 포커싱 되어있을때만 입력받도록.
		return E_FAIL;
	}

	//장치에 대한 access 버전을 받아옴.
	if (FAILED(m_pDInput8_Mouse->Acquire()))
	{
		return E_FAIL;
	}

	//m_tMouseButton_PreState = new BYTE[3];

	ZeroMemory(&m_tMouse_State, sizeof(DIMOUSESTATE));
	//ZeroMemory(&m_tMouseButton_PreState, sizeof(3));


	return S_OK;

}

void InputManager::Check_WindowFocus()
{
	//장치가 변수를 못받는다?
	//여러 요인이 있지만 보통 윈도우 포커스가 다른곳에 가서 그럼.
	//그래서 매프레임 장치 찾아옴

	//키보드의 입력 상태를 저장할 변수 넘겨줌
	if (FAILED(m_pDInput8_Keyboard->GetDeviceState(256, m_ucKeyboard_CurState)))
	{
		m_pDInput8_Keyboard->Acquire();
	}

	//마우스의 입력 상태를 저장할 구조체
	if (FAILED(m_pDInput8_Mouse->GetDeviceState(sizeof(m_tMouse_State), &m_tMouse_State)))
	{
		m_pDInput8_Mouse->Acquire();
	}
}

bool InputManager::GetKeyUp(const BYTE & _KeyVal)
{
	//전 프레임에서는 눌려져 있었지만, 현 프레임에서 눌러져 있지 않은 상태.
	if ((m_ucKeyboard_PreState[_KeyVal] & 0x80)
		&& !(m_ucKeyboard_CurState[_KeyVal] & 0x80))
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyDown(const BYTE & _KeyVal)
{
	//전 프레임에서는 안 눌러져있다가 현 프레임에서는 눌려진 상태
	if (!(m_ucKeyboard_PreState[_KeyVal] & 0x80)
		&& (m_ucKeyboard_CurState[_KeyVal] & 0x80))
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyPress(const BYTE & _KeyVal)
{
	//걍 현 프레임에서만 눌려져 있으면 됨.
	if (m_ucKeyboard_CurState[_KeyVal] & 0x80)

	{
		return true;
	}
	return false;
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

