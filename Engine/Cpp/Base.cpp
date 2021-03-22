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

	m_pRenderManager	= RenderManager::Get_Instance();
	m_pSceneManager		= SceneManager::Get_Instance();
}

Base::~Base()
{
	
}


void Base::Initialize(Desc * _desc)
{
	m_pDeviceManager->Initialize(_desc->hWnd, _desc->wincx, _desc->wincy, _desc->window);
	m_pTimeManager->Initialize();
	m_pInputManager->Initialize();

	m_pRenderManager->Initialize();
	m_pSceneManager->Initialize();
	
}

void Base::Process()
{
	//TimeManager
	//InputManager

	m_pSceneManager->Update();
	m_pSceneManager->LateUpdate();
	//Collision
	m_pSceneManager->Render();
	
}

void Base::Release()
{
}
