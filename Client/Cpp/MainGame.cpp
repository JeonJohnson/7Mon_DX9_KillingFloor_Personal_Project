#include "stdafx.h"
#include "..\Header\MainGame.h"
#include "Engine_Mother.h"
#include "TestScene.h"


Implement_Singleton(MainGame)

MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}

void MainGame::Initialize()
{
	Engine_Load();
	Scene_Setting();
	//m_pEngine = Engine_Mother::Get_Instance();
	//assert(L"Engine Load Failed" && m_pEngine);

	//Engine_Mother::Desc base_desc;
	//base_desc.wincx = WINCX;
	//base_desc.wincy = WINCY;
	//base_desc.window = false;
	//base_desc.hWnd = g_hWnd;

	//m_pEngine->Initialize(&base_desc);
	//
	//m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());

}

void MainGame::Release()
{
}

void MainGame::Engine_Load()
{
	m_pEngine = Engine_Mother::Get_Instance();
	assert(L"Engine Load Failed" && m_pEngine);

	Engine_Mother::Desc Engine_desc;
	Engine_desc.wincx = WINCX;
	Engine_desc.wincy = WINCY;
	Engine_desc.window = true;
	Engine_desc.hWnd = g_hWnd;

#ifdef _DEBUG
	Engine_desc.wincx_DEBUG = WINCX_DEBUG;
	Engine_desc.wincy_DEBUG = WINCY_DEBUG;
	Engine_desc.hWnd_DEBUG = g_hWnd_DEBUG;
#endif //_DEUBG

	Engine_desc.Object_Tag_MaxCount = OBJECT_TAG::OBJECT_TAG_END;
	Engine_desc.Render_Layer_MaxCount = RENDER_LAYER::RENDER_LAYER_End;
	

	m_pEngine->Initialize(&Engine_desc);
}

void MainGame::Scene_Setting()
{
	m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());
	m_pEngine->Init_Scene(L"Test_Scene");
}

void MainGame::Process()
{
	Engine_Mother::Get_Instance()->Process();
}

