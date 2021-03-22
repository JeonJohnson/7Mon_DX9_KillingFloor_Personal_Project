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

public:
	
private:

	
};

#endif 