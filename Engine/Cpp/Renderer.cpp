#include "..\Header\Renderer.h"

#include "DeviceManager.h"
#include "RenderManager.h"

Renderer::Renderer()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

	assert(L"Rednerer's Dx9 device is nullptr" && m_pDX9_Device);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
}

void Renderer::Update()
{
}

void Renderer::LateUpdate()
{
	
}

void Renderer::ReadyRender()
{
	//여기서 RenderManager의 RenderList에 보냄.
	RenderManager::Get_Instance()->Insert_RenderingList(this,m_iRenderLayer);
}

void Renderer::Release()
{
}
