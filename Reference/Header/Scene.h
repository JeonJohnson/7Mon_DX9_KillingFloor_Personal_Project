#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "Engine_Include.h"

class DLL_STATE Scene
{
	//���� �������� ������ scene���� state�־ ����Ҳ���.
	//scene�� ������ٰ� Init���� �ش� �� ���������ְ�
	 
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