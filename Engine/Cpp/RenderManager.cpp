#include "..\Header\RenderManager.h"
#include "DeviceManager.h"


Implement_Singleton(RenderManager)

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::Initialize()
{
	m_pD3D9_Device = DeviceManager::Get_Instance()->Get_D3D9_Device();
}

void RenderManager::Render()
{
	m_pD3D9_Device->Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	
	m_pD3D9_Device->BeginScene();

	Render_Priority();

	Render_NonAlpha();

	Render_Alpha();

	Render_UI();


	m_pD3D9_Device->EndScene();

	m_pD3D9_Device->Present(0, 0, 0, 0);
}

void RenderManager::Release()
{
}

void RenderManager::Render_Priority()
{
}

void RenderManager::Render_NonAlpha()
{
}

void RenderManager::Render_Alpha()
{
}

void RenderManager::Render_UI()
{
}

void RenderManager::Insert_RenderingList(Renderer * _renderer, int _order)
{
	
}


