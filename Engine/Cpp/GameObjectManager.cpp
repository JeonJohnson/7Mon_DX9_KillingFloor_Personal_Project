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
	for (auto& gameObject : m_vecGameObjectList)
	{
		gameObject->Update();
	}
}

void GameObjectManager::LateUpdate()
{
	for (auto& gameObject : m_vecGameObjectList)
	{
		gameObject->LateUpdate();
	}
}

void GameObjectManager::ReadyRender()
{
	for (auto& gameObject : m_vecGameObjectList)
	{
		gameObject->ReadyRender();
	}
}

void GameObjectManager::Release()
{

}

void GameObjectManager::ReleaseScene()
{


}

void GameObjectManager::Insert_GameObject(GameObject * _gameObject)
{
	assert(L"GameObject is nullptr" && _gameObject);

	m_vecGameObjectList.emplace_back(_gameObject);
}
