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
	void FPS_Update();

public:
	float Get_fTime() const
	{
		return m_fDeltaTime;
	};

	double	Get_dTime() const
	{
		return m_dDeltaTime;
	};
	
	int	Get_FPS() const;

	

private:
	LARGE_INTEGER	m_CpuTick;
	LARGE_INTEGER	m_BeginTime;
	LARGE_INTEGER	m_EndTime;

	double			m_dDeltaTime;
	float			m_fDeltaTime;
	
	float			m_fFPS_Time = 0.f;
	int				m_iFPS = 0;
	int				m_iFPS_Render = 0;

#pragma region ZedTime
	bool			m_bZedTime = false;
	float			m_fZedTime_Spd = 1.f;
	float			m_fZedTime_Delta;
	//킬플 만들꺼면 ZedTime기능 넣기 위해서
#pragma endregion
};

#endif //_TIME_MANAGER_H_