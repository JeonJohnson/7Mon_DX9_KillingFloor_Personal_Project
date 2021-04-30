#include "..\Header\GameObjectManager.h"


Implement_Singleton(GameObjectManager)

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	Release();
}

void GameObjectManager::Initailize(_object_Tag _maxCount)
{
	m_vecGameObjectList.assign(_maxCount, list<GameObject*>());
}

void GameObjectManager::Update()
{
	Merge_Gameobjects();
	Delete_DeadGameObjects();
	
	for (auto& ObjectList : m_vecGameObjectList)
	{
		for (auto& gameObject : ObjectList)
		{
			if (gameObject->Get_Active())
			{
				gameObject->Update();
			}
		}
	}
}

void GameObjectManager::LateUpdate()
{

	for (auto& ObjectList : m_vecGameObjectList)
	{
		for (auto& gameObject : ObjectList)
		{
			if (gameObject->Get_Active())
			{
				gameObject->LateUpdate();
			}
		}
	}

}

void GameObjectManager::ReadyRender()
{

	for (auto& ObjectList : m_vecGameObjectList)
	{
		for (auto& gameObject : ObjectList)
		{
			if (gameObject->Get_Active())
			{
				gameObject->ReadyRender();
			}
		}
	}
}

void GameObjectManager::Release()
{
	Merge_Gameobjects();

	for (auto& objectList : m_vecGameObjectList)
	{
		for (auto iter = objectList.begin(); iter != objectList.end();)
		{
			(*iter)->Release();

			delete *iter;
			iter = objectList.erase(iter);
		}

		if (objectList.size() > 0)
		{
			assert(0 && L"GameObjectList dont Release all");
		}

		objectList.clear();
	}

	m_vecGameObjectList.clear();
}

void GameObjectManager::Release_Scene()
{
	for (auto& objectList : m_vecGameObjectList)
	{
		for (auto iter = objectList.begin(); iter != objectList.end();)
		{
			if ((*iter)->Get_DontDestroy() == false)
			{
				(*iter)->Release();

				delete *iter;
				iter = objectList.erase(iter);
			}
			else { ++iter; }

		}
	}

	m_vecGameObjectList.shrink_to_fit();
}

void GameObjectManager::Merge_Gameobjects()
{
	if (m_newGameObjectList.size() == 0)
	{
		return;
	}

	for (auto& newObject : m_newGameObjectList)
	{
		int iTag = newObject->Get_Tag();

		m_vecGameObjectList[iTag].emplace_back(newObject);
		//터쳤던 이유
		//어쨋거나 바깥 vector에 인덱스 접근하는건데
		//씼팔아무것도 없는데 뭘 접근해 무친련,, 무친련,, 무친련,, 무친련,, 무친련,, 무친련,, 무친련,, 무친련,,

	}
	//m_vecGameObjectList.shrink_to_fit();

	m_newGameObjectList.clear();

}

void GameObjectManager::Delete_DeadGameObjects()
{
	for (auto& objectList : m_vecGameObjectList)
	{
		for (auto iter_obj = objectList.begin(); iter_obj != objectList.end();)
		{
			if ((*iter_obj)->Get_Alive() == false)
			{
				(*iter_obj)->Release();
				
				delete *iter_obj;
				iter_obj = objectList.erase(iter_obj);
			}
			else { ++iter_obj; }
		}
	}

	m_vecGameObjectList.shrink_to_fit();
}

GameObject * GameObjectManager::Get_GameObject(int _tag, const wstring & _name)
{
	if (m_vecGameObjectList[_tag].size() <= 0)
	{
		return nullptr;
	}
	else
	{
		for (auto& gameobject : m_vecGameObjectList[_tag])
		{
			if (gameobject->Get_Name() == _name)
			{
				return gameobject;
			}
		}
		
		
	}
	return nullptr;
}

GameObject * GameObjectManager::Get_GameObjectbyName(const wstring & _name)
{
	//Return First Object
	for (auto& objectList : m_vecGameObjectList)
	{
		for (auto& object : objectList)
		{
			if (object->Get_Name() == _name)
			{
				return object;
			}
		}
	}

	return nullptr;
}

GameObject * GameObjectManager::Get_GameObjectbyTag(int _tag)
{
	//Return First Object
	if (m_vecGameObjectList[_tag].size() > 0)
	{
		return m_vecGameObjectList[_tag].front();
	}
	else 
	{
		return nullptr;
	}
	
}

list<GameObject*> GameObjectManager::Get_GameObjectListbyTag(int _tag)
{
	if (m_vecGameObjectList[_tag].size() > 0)
	{
		return m_vecGameObjectList[_tag];
	}
	else { return list<GameObject*>(); }
}

void GameObjectManager::Insert_GameObject(GameObject * _gameObject)
{
	assert(L"GameObject is nullptr" && _gameObject);

	if (_gameObject != nullptr)
	{
		m_newGameObjectList.emplace_back(_gameObject);
	}


}
