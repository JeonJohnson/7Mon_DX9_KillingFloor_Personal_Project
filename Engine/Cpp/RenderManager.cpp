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
	
	if (FAILED(Update_ViewPort()))
	{
		MessageBox(0, L"ViewPort Setting Failed at RendererManager", L"Error", MB_OK);
	}
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
	//������ ������ �ȳ��´�? ������ "��"�����.
	
	m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//WrieFrame���� �׷��ִ°�.

	for (auto& renderer : m_RenderingList[0])
	{
		renderer->Render();
	}
}

void RenderManager::Render_NonAlpha()
{
	for (auto& renderer : m_RenderingList[1])
	{
		renderer->Render();
	}
}

void RenderManager::Render_Alpha()
{
	for (auto& renderer : m_RenderingList[2])
	{
		renderer->Render();
	}
}

void RenderManager::Render_UI()
{
	for (auto& renderer : m_RenderingList[3])
	{
		renderer->Render();
	}
}

HRESULT RenderManager::Update_ViewPort()
{
	//������ ����������
	/*
		1. ���� �����̽� : �� ������Ʈ���� ��ü ������ => ����, �Ž� 
			(���� ���)�� => �� ������Ʈ,������Ʈ�� transform������ ����.
		2. ���� �����̽� : ��Į �����̽��� ����� �ű� ��. 
			(�� ���)�� => ī�޶󿡼� ����.
		3. �� �����̽� : ���� �����̽��� (0,0,0) / z���ǹ����� �ٶ󺸴� ī�޶� �������� �ٲٴ°�.
		4. ���� ���� : 
		5. �ø� : 
			(���� ���)�� => ī�޶󿡼� ����.
		6. ��������(����) �����̽� : 3D���� ��ü���� 2D��ũ���� ����ϱ� ���� �ܰ�.
			-> �þ߰�, ȭ�������� �����ְ� 
			-> near�� far������� z�����⸦ ����.
		7. Ŭ���� : 
			(�� ��Ʈ ����)�� => RenderManager���� ���� ����.
		8. �� ��Ʈ : ������ �� ������ �������ִ°�.
		9. �����Ͷ����� : 
	*/
	D3DVIEWPORT9	tViewPort;
	tViewPort.X = 0; //ȭ���� ���� X��ǥ 
	tViewPort.Y = 0; //ȭ���� ���� Y��ǥ
	tViewPort.Width = (DWORD)DeviceManager::Get_Instance()->Get_WindowSize().x; //�ػ�x
	tViewPort.Height = (DWORD)DeviceManager::Get_Instance()->Get_WindowSize().y; //�ػ�y
	tViewPort.MinZ = 0.f; //Z���� �ּ�
	tViewPort.MaxZ = 1.f; //Z���� �ִ�

	if (FAILED(m_pDX9_Device->SetViewport(&tViewPort)))
	{
		return E_FAIL;
	}

	return S_OK;
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


