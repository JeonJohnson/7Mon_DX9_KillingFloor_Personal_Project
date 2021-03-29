#include "..\Header\GameObjectManager.h"


Implement_Singleton(GameObjectManager)

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Initailize()
{

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
	for (auto& objectList : m_vecGameObjectList)
	{
		for (auto iter = objectList.begin(); iter != objectList.end();)
		{
		
			(*iter)->Release();

			delete *iter;
			iter = objectList.erase(iter);
	
		}
	}

	m_vecGameObjectList.clear();
}

void GameObjectManager::ReleaseScene()
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
	for (auto& newObject : m_newGameObjectList)
	{
		int iTag = newObject->Get_Tag();

		m_vecGameObjectList[iTag].emplace_back(newObject);
	}
	m_vecGameObjectList.shrink_to_fit();

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

void GameObjectManager::Insert_GameObject(GameObject * _gameObject)
{
	assert(L"GameObject is nullptr" && _gameObject);

	if (_gameObject != nullptr)
	{
		m_newGameObjectList.emplace_back(_gameObject);
	}


}
