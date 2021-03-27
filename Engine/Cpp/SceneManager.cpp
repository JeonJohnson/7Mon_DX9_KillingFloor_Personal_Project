#include "SceneManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"

Implement_Singleton(SceneManager)

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//RenderManager::Get_Instance()->Initialize();

	// Test


}

void SceneManager::Update()
{
	GameObjectManager::Get_Instance()->Update();
}

void SceneManager::LateUpdate()
{
	GameObjectManager::Get_Instance()->LateUpdate();

}

void SceneManager::ReadyRender()
{
	GameObjectManager::Get_Instance()->ReadyRender();
}

void SceneManager::Render()
{
	RenderManager::Get_Instance()->Render();
}

void SceneManager::Release()
{
}
