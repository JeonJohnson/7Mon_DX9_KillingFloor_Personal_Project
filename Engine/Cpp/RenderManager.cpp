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
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

#ifdef _DEBUG
	m_pDX9_Device_DEBUG = DeviceManager::Get_Instance()->Get_DX9_Device_DEBUG();
#endif //_DEBUG
}

void RenderManager::Render()
{
	m_pDX9_Device->Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 255, 0, 255), 1.f, 0);
	
	m_pDX9_Device->BeginScene();

	Render_Priority();

	Render_NonAlpha();

	Render_Alpha();

	Render_UI();


	m_pDX9_Device->EndScene();

	m_pDX9_Device->Present(0, 0, 0, 0);
}

void RenderManager::Release()
{
}

void RenderManager::Render_Priority()
{
	//m_pDX9_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//도형에 색깔이 안나온다? 조명을 "꺼"줘야함.
	
	//m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//WrieFrame으로 그려주는것.

	for (auto& renderer : m_RenderingList[0])
	{
		renderer->Render();
	}
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
	m_RenderingList[_order].emplace_back(_renderer);
}

#ifdef _DEBUG
void RenderManager::Render_DEBUG()
{
	m_pDX9_Device_DEBUG->Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pDX9_Device_DEBUG->BeginScene();


	/*
	
	Debug Rendering
	
	*/



	m_pDX9_Device_DEBUG->EndScene();

	m_pDX9_Device_DEBUG->Present(0, 0, 0, 0);

}
#endif //_DEBUG


