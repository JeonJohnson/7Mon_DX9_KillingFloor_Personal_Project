#pragma once

#ifndef _TIME_MANAGER_H_
#define _TIME_MANAGER_H_

#include "Engine_Include.h"

class _declspec(dllexport) TimeManager
{

	Declare_Singleton(TimeManager)

private:
	TimeManager();
	~TimeManager();

public:
	void Initialize();
	void Update();

public:
	float Get_DeltaTime() const;
	

private:

	

};

#endif