#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "Engine_Include.h"

class DLL_STATE Scene
{
	//실제 스테이지 관리는 scene말고 state넣어서 사용할꺼임.
	//scene은 ㄹㅇ루다가 Init에서 해당 씬 설정만해주고
	 
	friend class SceneManager;

public:
	Scene();
	~Scene();

public:
	template <class T>
	static Scene* Instantiate()
	{
		return new T;
	}

protected:
	virtual void Initialize() = 0;



};


#endif