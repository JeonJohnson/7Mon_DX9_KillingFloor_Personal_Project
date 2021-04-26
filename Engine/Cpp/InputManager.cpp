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

void InputManager::Initialize(HINSTANCE hInst, HWND hWnd, bool _IsEngine)
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


	if (FAILED(Keyboard_Create(hWnd, _IsEngine)))
	{
		assert(0 && L"Keyboard Create is failed");
	}

	if (FAILED(Mouse_Create(hWnd, _IsEngine)))
	{
		assert(0 && L"Mouse Create is failed");
	}



}

void InputManager::Update()
{
	//Ű���� �� �������̶� ���ϱ� ���ؼ� 
	unsigned char*	Keyboard_TempState = m_ucKeyboard_PreState;
	m_ucKeyboard_PreState = m_ucKeyboard_CurState;
	m_ucKeyboard_CurState = Keyboard_TempState;

	//���콺 �� �������̶� ���ϱ� ���ؼ�
	//for (int i = 0; i < 4; ++i)
	//{
	//	m_tMouseButton_PreState[i] = m_tMouse_State.rgbButtons[i];
	//}
	memcpy(m_tMouseButton_PreState, m_tMouse_State.rgbButtons, sizeof(BYTE)*4);

	Check_WindowFocus();

	////Ű������ �Է� ���¸� ������ ���� �Ѱ���
	//m_pDInput8_Keyboard->GetDeviceState(256, m_ucKeyboard_CurState);
	////���콺�� �Է� ���¸� ������ ����ü
	//m_pDInput8_Mouse->GetDeviceState(sizeof(m_tMouse_State), &m_tMouse_State);
	
}

void InputManager::Release()
{
	Safe_Delete(m_ucKeyboard_CurState);
	Safe_Delete(m_ucKeyboard_PreState);
	m_pDInput8_Keyboard->Unacquire();
	Safe_Release(m_pDInput8_Keyboard);
	
	Safe_Delete_Arr(m_tMouseButton_PreState);
	m_pDInput8_Mouse->Unacquire();
	Safe_Release(m_pDInput8_Mouse);

	Safe_Release(m_pDInput8_SDK);
}

HRESULT InputManager::Keyboard_Create(HWND hWnd, bool _IsEngine)
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
	//DISCL_FOREGROUND | DISCL_EXCLUSIVE : ȭ�� �ȿ��� ���콺 �Ⱥ��̰� Ȱ��ȭ �����϶��� �۵�
	if (FAILED(m_pDInput8_Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		//=> Ŭ���̾�Ʈ�� ��Ŀ�� �Ǿ��������� �Է¹޵���.
		return E_FAIL;
	}

	//��ġ�� ���� access ������ �޾ƿ�.
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

HRESULT InputManager::Mouse_Create(HWND hWnd, bool _IsEngine)
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
	//DISCL_FOREGROUND | DISCL_EXCLUSIVE : ȭ�� �ȿ��� ���콺 �Ⱥ��̰� Ȱ��ȭ �����϶��� �۵�
	//DISCL_BACKGROUND | DISCL_NONEXCLUSIVE : �ݴ�
	if (!_IsEngine)
	{
		if (FAILED(m_pDInput8_Mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			//=> Ŭ���̾�Ʈ�� ��Ŀ�� �Ǿ��������� �Է¹޵���.
			return E_FAIL;
		}
	}
	else 
	{
		if (FAILED(m_pDInput8_Mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			//=> Ŭ���̾�Ʈ�� ��Ŀ�� �Ǿ��������� �Է¹޵���.
			return E_FAIL;
		}
	}
	

	//��ġ�� ���� access ������ �޾ƿ�.
	if (FAILED(m_pDInput8_Mouse->Acquire()))
	{
		return E_FAIL;
	}

	m_tMouseButton_PreState = new BYTE[4];
	////int temp = sizeof(BYTE);
	//ZeroMemory(&m_tMouseButton_PreState, sizeof(4));

	ZeroMemory(&m_tMouse_State, sizeof(DIMOUSESTATE));
	


	return S_OK;

}

void InputManager::Check_WindowFocus()
{
	//��ġ�� ������ ���޴´�?
	//���� ������ ������ ���� ������ ��Ŀ���� �ٸ����� ���� �׷�.
	//�׷��� �������� ��ġ ã�ƿ�

	//Ű������ �Է� ���¸� ������ ���� �Ѱ���
	if (FAILED(m_pDInput8_Keyboard->GetDeviceState(256, m_ucKeyboard_CurState)))
	{
		m_pDInput8_Keyboard->Acquire();
	}

	//���콺�� �Է� ���¸� ������ ����ü
	if (FAILED(m_pDInput8_Mouse->GetDeviceState(sizeof(m_tMouse_State), &m_tMouse_State)))
	{
		m_pDInput8_Mouse->Acquire();
	}
}

bool InputManager::GetKeyUp(BYTE _KeyVal)
{
	//�� �����ӿ����� ������ �־�����, �� �����ӿ��� ������ ���� ���� ����.
	if ((m_ucKeyboard_PreState[_KeyVal] & 0x80)
		&& !(m_ucKeyboard_CurState[_KeyVal] & 0x80))
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyDown(BYTE _KeyVal)
{
	//�� �����ӿ����� �� �������ִٰ� �� �����ӿ����� ������ ����
	if (!(m_ucKeyboard_PreState[_KeyVal] & 0x80)
		&& (m_ucKeyboard_CurState[_KeyVal] & 0x80))
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyPress(BYTE  _KeyVal)
{
	//�� �� �����ӿ����� ������ ������ ��.
	if (m_ucKeyboard_CurState[_KeyVal] & 0x80)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseUp(int _MouseVal)
{
	//�� �����ӿ����� ������ �־�����, �� �����ӿ��� ������ ���� ���� ����.
	if ((m_tMouseButton_PreState[_MouseVal] & 0x80)
		&& !(m_tMouse_State.rgbButtons[_MouseVal] & 0x80))
	{
		return true;
	}

	return false;
}

bool InputManager::GetMouseDown(int _MouseVal)
{
	//�� �����ӿ����� �� �������ִٰ� �� �����ӿ����� ������ ����
	if (!(m_tMouseButton_PreState[_MouseVal] & 0x80)
		&& (m_tMouse_State.rgbButtons[_MouseVal] & 0x80))
	{
		return true;
	}

	return false;
}

bool InputManager::GetMousePress(int _MouseVal)
{
	if (m_tMouse_State.rgbButtons[_MouseVal] & 0x80)
	{
		return true;
	}
	return false;
}

int InputManager::GetMouseMove(int _MouseMove)
{
	return (int)(*(((LONG*)&m_tMouse_State) + _MouseMove));
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

