#pragma once

#ifndef _GAMEOBJECT_MANAGER_H_
#define _GAMEOBJECT_MANAGER_H_

#include "Engine_Include.h"	

#include "GameObject.h"

class GameObjectManager
{
	Declare_Singleton(GameObjectManager)

private:
	GameObjectManager();
	~GameObjectManager();
	
public:
	void Initailize();
	void Update();
	void LateUpdate();
	void Release();

public:

public:

private:
	map<int, GameObject*>	m_mGameObjectList;
	
};

#endif