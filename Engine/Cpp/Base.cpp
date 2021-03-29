#include "..\Header\Base.h"

Base*	Base::m_Instance = nullptr;

Base * Base::Get_Instance()
{
	if (!m_Instance)
	{
		m_Instance = new Base;
	}
	return m_Instance;
}

void Base::Destroy_Instance()
{
	if (m_Instance)
	{
		delete	m_Instance;
		m_Instance = nullptr;
	}
}

Base::Base()
{
	m_pDeviceManager	= DeviceManager::Get_Instance();
	m_pTimeManager		= TimeManager::Get_Instance();
	m_pInputManager		= InputManager::Get_Instance();

	m_pGameObjectManager = GameObjectManager::Get_Instance();
	m_pRenderManager	= RenderManager::Get_Instance();
	m_pSceneManager		= SceneManager::Get_Instance();
}

Base::~Base()
{
	
}


void Base::Initialize(Desc * _desc)
{
	m_pDeviceManager->Initialize(_desc->hWnd, _desc->wincx, _desc->wincy, _desc->window);
	m_pTimeManager->Time_Init();
	m_pInputManager->Initialize();

	m_pGameObjectManager->Initailize();
	m_pRenderManager->Initialize();
	m_pSceneManager->Initialize();
	
}

void Base::Process()
{
	m_pTimeManager->Time_Update();
	m_pInputManager->Update();

	m_pSceneManager->Update();
	m_pSceneManager->LateUpdate();
	m_pSceneManager->ReadyRender();
	//Collision
	m_pSceneManager->Render();
	
}

void Base::Release()
{
	m_pSceneManager->Destroy_Instance();
	m_pRenderManager->Destroy_Instance();
	m_pGameObjectManager->Destroy_Instance();
	m_pInputManager->Destroy_Instance();
	m_pTimeManager->Destroy_Instance();

	m_pDeviceManager->Destroy_Instance();
}

LPDIRECT3DDEVICE9 Base::Get_Dx9_Device() const
{
	return m_pDeviceManager->Get_DX9_Device();
}

float Base::Get_DeltaTime() const
{
	return m_pTimeManager->Get_Time();
}

void Base::Add_Scene(const wstring & _wName, Scene * _pScene)
{
	m_pSceneManager->Insert_Scene(_wName, _pScene);
}

void Base::Load_Scene(const wstring & _wName)
{
	m_pSceneManager->Load_Scene(_wName);
}

void Base::Init_Scene(const wstring & _wName)
{
	m_pSceneManager->Set_FirstScene(_wName);
}
