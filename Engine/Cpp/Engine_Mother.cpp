#include "..\Header\Engine_Mother.h"

Engine_Mother*	Engine_Mother::m_Instance = nullptr;

Engine_Mother * Engine_Mother::Get_Instance()
{
	if (!m_Instance)
	{
		m_Instance = new Engine_Mother;
	}
	return m_Instance;
}

void Engine_Mother::Destroy_Instance()
{
	if (m_Instance)
	{
		delete	m_Instance;
		m_Instance = nullptr;
	}
}

Engine_Mother::Engine_Mother()
{
	m_pDeviceManager		= DeviceManager::Get_Instance();
	m_pTimeManager			= TimeManager::Get_Instance();
	m_pInputManager			= InputManager::Get_Instance();
	m_pResourceManager		= ResourceManager::Get_Instance();

	m_pGameObjectManager	= GameObjectManager::Get_Instance();
	m_pRenderManager		= RenderManager::Get_Instance();
	m_pSceneManager			= SceneManager::Get_Instance();
}

Engine_Mother::~Engine_Mother()
{
	
}


void Engine_Mother::Initialize(Desc * _desc)
{
	m_pDeviceManager->Initialize(_desc->hWnd, _desc->wincx, _desc->wincy, _desc->window);
#ifdef _DEBUG
	m_pDeviceManager->Ready_DX9_Device_DEBUG(_desc->hWnd_DEBUG,
		_desc->wincx_DEBUG, _desc->wincy_DEBUG);
#endif //_DEBUG
	m_pTimeManager->Time_Init();
	m_pInputManager->Initialize();
	m_pResourceManager->Initialize();

	m_pGameObjectManager->Initailize(_desc->Object_Tag_MaxCount);
	m_pRenderManager->Initialize();
	m_pSceneManager->Initialize();

	
	
}

void Engine_Mother::Process()
{
	m_pTimeManager->Time_Update();
	m_pInputManager->Update();

	m_pSceneManager->Update();
	m_pSceneManager->LateUpdate();
	m_pSceneManager->ReadyRender();
	//Collision
	m_pSceneManager->Render();

	
}

void Engine_Mother::Release()
{
	m_pSceneManager->Destroy_Instance();
	m_pRenderManager->Destroy_Instance();
	m_pGameObjectManager->Destroy_Instance();
	m_pInputManager->Destroy_Instance();
	m_pTimeManager->Destroy_Instance();

	m_pDeviceManager->Destroy_Instance();
}

LPDIRECT3DDEVICE9 Engine_Mother::Get_Dx9_Device() const
{
	return m_pDeviceManager->Get_DX9_Device();
}

float Engine_Mother::Get_DeltaTime() const
{
	return m_pTimeManager->Get_Time();
}

void Engine_Mother::Add_Scene(const wstring & _wName, Scene * _pScene)
{
	m_pSceneManager->Insert_Scene(_wName, _pScene);
}

void Engine_Mother::Load_Scene(const wstring & _wName)
{
	m_pSceneManager->Load_Scene(_wName);
}

void Engine_Mother::Init_Scene(const wstring & _wName)
{
	m_pSceneManager->Set_FirstScene(_wName);
}
