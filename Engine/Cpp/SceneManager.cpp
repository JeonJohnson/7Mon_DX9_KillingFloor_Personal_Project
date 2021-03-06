#include "SceneManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"
#include "UIManager.h"



Implement_Singleton(SceneManager)

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Initialize()
{

}

void SceneManager::Update()
{
	SceneChangeCheck();

	CurrentSceneCheck();

	GameObjectManager::Get_Instance()->Update();
	ResourceManager::Get_Instance()->Update();
}

void SceneManager::LateUpdate()
{
	CurrentSceneCheck();

	GameObjectManager::Get_Instance()->LateUpdate();
}

void SceneManager::ReadyRender()
{
	CurrentSceneCheck();

	GameObjectManager::Get_Instance()->ReadyRender();
}

void SceneManager::Render()
{
	CurrentSceneCheck();

	
	RenderManager::Get_Instance()->Render();
#ifdef _DEBUG
	RenderManager::Get_Instance()->Render_DEBUG();
#endif //_DEBUG

}

void SceneManager::Release()
{
	//GameObjectManager::Get_Instance()->Release();
	//RenderManager::Get_Instance()->Release();

	for (auto iter = m_mapSceneList.begin(); iter != m_mapSceneList.end();)
	{
		delete (*iter).second;
		(*iter).second = nullptr;
		iter = m_mapSceneList.erase(iter);
	}

	if (m_mapSceneList.size() > 0)
	{
		assert(0 && L"scene Release");
	}


}

void SceneManager::CurrentSceneCheck()
{
	assert(L"CheckOut CurrentScene...!" && m_pCurrentScene);
}

void SceneManager::Insert_Scene(const wstring & _wName, Scene* _pScene)
{
	int i = 0;

	if (m_mapSceneList[_wName])
	{
		assert(0&&L"Scene Name is already Exist");

		return;
	}
	
	m_mapSceneList[_wName] = _pScene;
}

void SceneManager::Set_FirstScene(const wstring & _wName)
{
	assert(L"?׷? ?̸? ?? ???µ???????;" && m_mapSceneList[_wName]);

	if (m_pCurrentScene == nullptr)
	{
		m_pCurrentScene = m_mapSceneList[_wName];
		m_pCurrentScene->Initialize();
	}

}

void SceneManager::Load_Scene(const wstring & _wName)
{
	m_bNext = true;
	m_pNextScene = m_mapSceneList[_wName];
	assert(L"?׷? ?̸? ?? ???µ???????;" && m_pNextScene);
}

void SceneManager::SceneChangeCheck()
{
	if (m_bNext)
	{
		assert(L"NextScene is nullptr" && m_pNextScene);

		m_bNext = false;

		//?׿ɢh?޴??????? ?ɢhƮ?? ?? ?????ֱ?
		GameObjectManager::Get_Instance()->Release_Scene();
		UIManager::Get_Instance()->Release_Scene();

		m_pCurrentScene = m_pNextScene;
		m_pCurrentScene->Initialize();

		m_pNextScene = nullptr;
	}
}

