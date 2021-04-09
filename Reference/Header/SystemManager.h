#pragma once

#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_

#include "Engine_Include.h"

class SystemManager
{
	Declare_Singleton(SystemManager)

//어디에 쓰징ㅋㅋ
//FPS출력도 걍 GameObject로 할거같은데

private:
	SystemManager();
  ~SystemManager();

public:
	void Initailize();
	void Update();
	void LateUpdate();
	void ReadyRender();
	void Release();

};

#endif //_SYSTEM_MANAGER_H_