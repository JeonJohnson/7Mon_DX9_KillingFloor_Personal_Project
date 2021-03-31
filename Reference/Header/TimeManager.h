#pragma once

#ifndef _TIME_MANAGER_H_
#define _TIME_MANAGER_H_

#include "Engine_Include.h"

class DLL_STATE TimeManager
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
	
#pragma region ZedTime
	bool			m_bZedTime = false;
	float			m_fZedTime_Spd = 1.f;
	float			m_fZedTime_Delta;
	//킬플 만들꺼면 ZedTime기능 넣기 위해서
#pragma endregion
};

#endif //_TIME_MANAGER_H_