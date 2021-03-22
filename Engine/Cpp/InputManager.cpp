#include "..\Header\InputManager.h"


Implement_Singleton(InputManager)

InputManager::InputManager() 
	:m_dwKey(0), m_dwKeyDown(0), m_dwKeyUp(0)
{
}


InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
}

void InputManager::Update()
{

}

void InputManager::Release()
{
}

bool InputManager::GetKeyUp(const DWORD & _dwKey)
{
	if (m_dwKey & _dwKey)
	{
		m_dwKeyUp |= _dwKey;
		return false;
	}
	else if (m_dwKeyUp & _dwKey)
	{
		m_dwKeyUp ^= _dwKey;
		return true;
	}
	return false;
}

bool InputManager::GetKeyDown(const DWORD & _dwKey)
{
	if ((m_dwKey & _dwKey) && !(m_dwKeyDown & _dwKey))
	{
		m_dwKeyDown |= _dwKey;
		return true;
	}
	else if (!(m_dwKey & _dwKey) && (m_dwKeyDown & _dwKey))
	{
		m_dwKeyDown ^= _dwKey;
		return false;
	}
	return false;
}

bool InputManager::GetKeyPress(const DWORD & _dwKey)
{
	if (m_dwKey & _dwKey)
	{
		return true;
	}
	return false;
}

