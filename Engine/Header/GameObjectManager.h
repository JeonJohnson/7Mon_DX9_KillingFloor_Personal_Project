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
	void Initailize(_object_Tag _maxCount);
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
	vector<list<GameObject*>>			m_vecGameObjectList;
	//map 쓸라니까 좀 tag값 지정해주기 귀찮넹 ㅎㅎ;
	//어차피 tag값 enum으로 int값인디 vector로 해주자
	
	//new GameObjList는 어차피 따로 접근 할 일 없이 다음 프레임에 넘겨줄꺼니까
	//추가에 비용이 얼마안드는 list해줄까..?

	//Tag값에 따라 다르게 저장해줘야해서 map이 편할거 같지만
	//map을 []접근해서 삽입하는거 실수하면 다 날라가긴한데... 고민중
	//준엽이형의 오늘의 리빙포인트
	//맵 삽입시[key] 의 값이 있는지 없는지 확인한 다음 없을떄 [key]삽입이 젤루 낫다고 하심.
};

#endif //_GAMEOBJECT_MANAGER_H_