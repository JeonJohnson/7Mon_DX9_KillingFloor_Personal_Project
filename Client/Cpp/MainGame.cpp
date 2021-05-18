#include "stdafx.h"
#include "..\Header\MainGame.h"
#include "Engine_Mother.h"
#include "TestScene.h"
#include "Text.h"
#include "IntroScene.h"
#include "MainMenuScene.h"
#include "StageScene.h"
#include "WeaponManager.h"



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
	FPS_RenderSetting();

	srand((unsigned int)time(NULL));
}

void MainGame::Release()
{
	Client_Release();
	m_pEngine->Release();
	m_pEngine->Destroy_Instance();
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
	Engine_desc.hInst = hInst;

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
	//m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());
	//m_pEngine->Init_Scene(L"Test_Scene");

	m_pEngine->Add_Scene(L"Intro_Scene", Scene::Instantiate<IntroScene>());
	m_pEngine->Add_Scene(L"MainMenu_Scene", Scene::Instantiate<MainMenuScene>());
	m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());
	m_pEngine->Add_Scene(L"Stage_Scene", Scene::Instantiate<StageScene>());
	m_pEngine->Init_Scene(L"Test_Scene");
}

void MainGame::Client_Release()
{
	WeaponManager::Get_Instance()->Release();
}

void MainGame::FPS_RenderSetting()
{
	//GameObject* FPS_Renderer = INSTANTIATE(OJBECT_TAG_UI, L"FPS_Renderer");

	UI*			FPS_Renderer = INSTANTIATE_UI(L"FPS_Renderer", true);
	FPS_Renderer->Set_Position(Vector3(50,50,0));

	Text::Desc fps_text;
	fps_text.iHeight = 14;
	fps_text.iWeight = FW_HEAVY;
	fps_text.ulOption = DT_LEFT|DT_NOCLIP;
	fps_text.szScript = L"FPS : ";
	fps_text.tColor = D3DCOLOR_RGBA(0, 255, 0, 255);

	FPS_Renderer->Add_UIComponent<Text>(&fps_text);
	
	
	m_pFPS = FPS_Renderer->Get_UIComponent<Text>();

	//string strName = typeid(Text).name();


	//Sprite::Desc sprite;
	//FPS_Renderer->Add_UIComponent<Sprite>(&sprite);
}

void MainGame::FPS_Update()
{
	wstring szFPS = L"FPS : " + to_wstring(EngineFunction->Get_FPS());
	
	m_pFPS->Set_Script(szFPS);
}

void MainGame::Process()
{
	FPS_Update();
	Engine_Mother::Get_Instance()->Process();

}

