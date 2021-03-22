#include "..\Header\SceneManager.h"
#include "RenderManager.h"

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
}

void SceneManager::Update()
{
	

}

void SceneManager::LateUpdate()
{


}

void SceneManager::Render()
{
	RenderManager::Get_Instance()->Render();
}

void SceneManager::Release()
{
}
