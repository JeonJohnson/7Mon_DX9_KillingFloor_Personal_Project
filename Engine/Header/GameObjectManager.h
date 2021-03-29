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
	void ReleaseScene();
	
	void Merge_Gameobjects();
	void Delete_DeadGameObjects();

public: /* Get */

public: /* Set */
	void	Insert_GameObject(GameObject* _gameObject);

private:
	list<GameObject*>					m_newGameObjectList;
	map<int, list<GameObject*>>			m_mapGameObjectList;
	//int -> Object Tag Value

	//new GameObjList는 어차피 따로 접근 할 일 없이 다음 프레임에 넘겨줄꺼니까
	//추가에 비용이 얼마안드는 list해줄까..?

	//Tag값에 따라 다르게 저장해줘야해서 map이 편할거 같지만
	//map을 []접근해서 삽입하는거 실수하면 다 날라가긴한데... 고민중
	//준엽이형의 오늘의 리빙포인트
	//맵 삽입시[key] 의 값이 있는지 없는지 확인한 다음 없을떄 [key]삽입이 젤루 낫다고 하심.
};

#endif