#pragma once

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "Engine_Include.h"

class _declspec(dllexport) InputManager
{

	Declare_Singleton(InputManager)

private:
	InputManager();
	~InputManager();

public:
	void Initialize();
	void Update();
	void Release();

public:
	bool	GetKeyUp(const DWORD & _dwKey);
	bool	GetKeyDown(const DWORD & _dwKey);
	bool	GetKeyPress(const DWORD & _dwKey);

public:
	
private:
	DWORD m_dwKey;
	DWORD m_dwKeyUp;
	DWORD m_dwKeyDown;

	
};

#endif 