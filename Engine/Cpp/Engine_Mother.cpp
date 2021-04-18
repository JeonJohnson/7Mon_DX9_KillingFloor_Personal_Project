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
	m_pUiManager			= UIManager::Get_Instance();
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
	m_pInputManager->Initialize(_desc->hInst, _desc->hWnd);
	m_pResourceManager->Initialize();

	m_pGameObjectManager->Initailize(_desc->Object_Tag_MaxCount);
	m_pUiManager->Initailize();
	m_pRenderManager->Initialize();
	m_pSceneManager->Initialize();
	
}

void Engine_Mother::Initialize(Desc_Tool * _desc)
{
	m_pDeviceManager->Initialize(_desc->hWnd_forDevice, _desc->wincx, _desc->wincy, true);
	m_pTimeManager->Time_Init();
	m_pInputManager->Initialize(_desc->hInst, _desc->hWnd_forDInput);
	m_pResourceManager->Initialize();

	m_pGameObjectManager->Initailize(_desc->Object_Tag_MaxCount);
	m_pUiManager->Initailize();
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
	//m_pRenderManager->Render_DEBUG();
	//Collision
	m_pSceneManager->Render();
}

void Engine_Mother::Release()
{
	m_pSceneManager->Destroy_Instance();
	m_pRenderManager->Destroy_Instance();
	m_pUiManager->Destroy_Instance();
	m_pGameObjectManager->Destroy_Instance();
	m_pInputManager->Destroy_Instance();
	m_pTimeManager->Destroy_Instance();

	m_pResourceManager->Destroy_Instance();

	m_pDeviceManager->Destroy_Instance();
}

LPDIRECT3DDEVICE9 Engine_Mother::Get_Dx9_Device() const
{
	return m_pDeviceManager->Get_DX9_Device();
}

LPD3DXSPRITE Engine_Mother::Get_DX9_Sprite() const
{
	return m_pDeviceManager->Get_DX9_Sprite();
}

#ifdef _DEBUG
LPDIRECT3DDEVICE9 Engine_Mother::Get_Dx9_Device_DEBUG() const
{
	return m_pDeviceManager->Get_DX9_Device_DEBUG();
}
#endif //_DEBUG


float Engine_Mother::Get_DeltaTime() const
{
	return m_pTimeManager->Get_Time();
}

int Engine_Mother::Get_FPS() const
{
	return m_pTimeManager->Get_FPS();
}

bool Engine_Mother::GetKeyUp(const BYTE & _keyValue)
{
	return m_pInputManager->Get_Instance()->GetKeyUp(_keyValue);
}

bool Engine_Mother::GetKeyDown(const BYTE & _keyValue)
{
	return m_pInputManager->Get_Instance()->GetKeyDown(_keyValue);
}

bool Engine_Mother::GetKeyPress(const BYTE & _keyValue)
{
	return m_pInputManager->Get_Instance()->GetKeyPress(_keyValue);
}

bool Engine_Mother::GetMouseUp(int _MouseVal)
{
	return m_pInputManager->Get_Instance()->GetMouseUp(_MouseVal);
}

bool Engine_Mother::GetMouseDown(int _MouseVal)
{
	return m_pInputManager->Get_Instance()->GetMouseDown(_MouseVal);
}

bool Engine_Mother::GetMousePress(int _MouseVal)
{
	return m_pInputManager->Get_Instance()->GetMousePress(_MouseVal);
}

int Engine_Mother::GetMouseMove(int _MouseMove)
{
	return m_pInputManager->Get_Instance()->GetMouseMove(_MouseMove);
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

GameObject * Engine_Mother::Get_GameObject(int _tag, const wstring & _name)
{
	return m_pGameObjectManager->Get_GameObject(_tag, _name);
}

GameObject * Engine_Mother::Get_GameObjectbyName(const wstring & _name)
{
	return m_pGameObjectManager->Get_GameObjectbyName(_name);
}

GameObject * Engine_Mother::Get_GameObjectbyTag(int _tag)
{
	return m_pGameObjectManager->Get_GameObjectbyTag(_tag);
}

void Engine_Mother::Load_Texture(const wstring & _wPath, const wstring & _wName)
{
	m_pResourceManager->Load_Texture(_wPath, _wName);
}

void Engine_Mother::Load_StaticMesh(const wstring & _szMeshPath, const wstring & _szTexPath, const wstring & _szMeshName)
{
	m_pResourceManager->Load_StaticMesh(_szMeshPath, _szTexPath, _szMeshName);
}

void Engine_Mother::Load_AnimMesh(const wstring & _szMeshPath, const wstring & _szMeshName)
{
	m_pResourceManager->Load_AnimMesh(_szMeshPath, _szMeshName);
}
