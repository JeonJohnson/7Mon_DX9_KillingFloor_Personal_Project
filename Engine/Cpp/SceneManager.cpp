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
	// Test


}

void SceneManager::Update()
{
	SceneChangeCheck();

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
	GameObjectManager::Get_Instance()->Release();
	RenderManager::Get_Instance()->Release();
}

void SceneManager::Insert_Scene(const wstring & _wName)
{

}

void SceneManager::Load_Scene(const wstring & _wSceneName)
{
	m_pNextScene = m_mapSceneList[_wSceneName];
	assert(L"NextScene error" && m_pNextScene);
	m_bNext = true;
}

void SceneManager::SceneChangeCheck()
{
	if (m_bNext)
	{
		assert(L"NextScene is nullptr" && m_pNextScene);

		m_bNext = false;

		//겜옵줵메니저에서 옵줵트들 다 지워주기
		m_pCurrentScene = m_pNextScene;
	}
}

