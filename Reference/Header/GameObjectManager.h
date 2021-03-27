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
	void ReadyRender();
	void Release();

public: /* functions */

public: /* Get */

public: /* Set */
	void	Insert_GameObject(GameObject* _gameObject);

private:
	vector<GameObject*>				m_vecGameObjectList;
	//map<int, list<GameObject*>>	m_vecGameObjectList;	
};

#endif