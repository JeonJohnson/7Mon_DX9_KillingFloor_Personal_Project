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
	void Time_Init();

	void Time_Update();

public:
	float Get_Time()
	{
		return m_fDeltaTime;
	};
	

private:
	LARGE_INTEGER	m_CpuTick;
	LARGE_INTEGER	m_BeginTime;
	LARGE_INTEGER	m_EndTime;

	float			m_fDeltaTime;
	
};

#endif