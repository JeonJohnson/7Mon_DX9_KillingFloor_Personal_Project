#include "stdafx.h"
#include "..\Header\MainGame.h"
#include "Base.h"
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

	m_pEngine = Base::Get_Instance();
	assert(L"Engine Load Failed" && m_pEngine);

	Base::Desc base_desc;
	base_desc.wincx = WINCX;
	base_desc.wincy = WINCY;
	base_desc.window = false;
	base_desc.hWnd = g_hWnd;

	m_pEngine->Initialize(&base_desc);
	
	m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());

}

void MainGame::Release()
{
}

void MainGame::Engine_Load()
{
	m_pEngine = Base::Get_Instance();
	assert(L"Engine Load Failed" && m_pEngine);

	Base::Desc base_desc;
	base_desc.wincx = WINCX;
	base_desc.wincy = WINCY;
	base_desc.window = false;
	base_desc.hWnd = g_hWnd;

	m_pEngine->Initialize(&base_desc);
}

void MainGame::Scene_Setting()
{
	m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());

}

void MainGame::Process()
{
	Base::Get_Instance()->Process();
}
