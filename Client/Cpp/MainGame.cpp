#include "stdafx.h"
#include "..\Header\MainGame.h"
#include "Engine_Mother.h"
#include "TestScene.h"
#include "Text.h"



Implement_Singleton(MainGame)

MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}

void MainGame::Initialize()
{

	//assert(0 && L"assert Test");

	Engine_Load();
	Scene_Setting();
	FPS_RenderSetting();
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

//	GameObject* FPS_Renderer = INSTANTIATE(OJBECT_TAG_UI, L"FPS");
//	
//	Text::Desc FPS_Desc;
//#ifdef _DEBUG
//	FPS_Desc.Dx9Device = EngineFunction->Get_Dx9_Device_DEBUG();
//#else
//	FPS_Desc.Dx9Device = EngineFunction->Get_Dx9_Device();
//#endif //_DEBUG
//	FPS_Renderer->Add_Component<Text>(&FPS_Desc);
//	
//	m_pFPS = FPS_Renderer->Get_NewComponent<Text>();
//
//	EngineFunction->Set_FPSText(m_pFPS);

}

void MainGame::Release()
{
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
	m_pEngine->Add_Scene(L"Test_Scene", Scene::Instantiate<TestScene>());
	m_pEngine->Init_Scene(L"Test_Scene");
}

void MainGame::FPS_RenderSetting()
{
	//GameObject* FPS_Renderer = INSTANTIATE(OJBECT_TAG_UI, L"FPS_Renderer");

	UI*			FPS_Renderer = INSTANTIATE_UI(L"FPS_Renderer");
	FPS_Renderer->Set_Position(Vector3(50,50,0));

	Text::Desc fps_text;
	fps_text.iHeight = 20;
	fps_text.iWeight = FW_EXTRABOLD;
	fps_text.ulOption = DT_LEFT;
	fps_text.szScript = L"FPS : ";

	FPS_Renderer->Add_UIComponent<Text>(&fps_text);

	//Sprite::Desc sprite;
	//FPS_Renderer->Add_UIComponent<Sprite>(&sprite);
}

void MainGame::Process()
{
	Engine_Mother::Get_Instance()->Process();
	
}

