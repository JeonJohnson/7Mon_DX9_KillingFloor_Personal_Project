#include "..\Header\RenderManager.h"
#include "DeviceManager.h"
#include "TimeManager.h"
#include "UIManager.h"

#include "ResourceManager.h"
#include "Texture.h"

Implement_Singleton(RenderManager)

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Initialize()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	m_pDX9_Sprite = DeviceManager::Get_Instance()->Get_DX9_Sprite();

	assert(L"RenderManager coms Failed" && (m_pDX9_Device || m_pDX9_Sprite));

#ifdef _DEBUG
	m_pDX9_Device_DEBUG = DeviceManager::Get_Instance()->Get_DX9_Device_DEBUG();
	
#endif //_DEBUG
	
	if (FAILED(Update_ViewPort()))
	{
		MessageBox(0, L"ViewPort Setting Failed at RendererManager", L"Error", MB_OK);
	}

	{/*test*/
		D3DXFONT_DESCW	tFontInfo;
		ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

		tFontInfo.Height = 20;
		//tFontInfo.Width = 20;
		tFontInfo.Weight = FW_SEMIBOLD; // �β�
		//tFontInfo.CharSet = HANGEUL_CHARSET; //�ѱ���Ʈ�϶���
		//lstrcpy(tFontInfo.FaceName, L"Ubuntu");

		D3DXCreateFontIndirect(m_pDX9_Device, &tFontInfo, &m_pTempFont);
	}


}

void RenderManager::Render()
{
	m_pDX9_Device->Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 255, 222, 222), 1.f, 0);
	
	m_pDX9_Device->BeginScene();

	Render_Priority();

	Render_NonAlpha();

	Render_Alpha();

	Render_UI();


	m_pDX9_Device->EndScene();

	m_pDX9_Device->Present(0, 0, 0, 0);
	
	Clear_RenderingList();
}

void RenderManager::Release()
{
	Clear_RenderingList();
}

void RenderManager::Render_Priority()
{
	m_pDX9_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//������ ������ �ȳ��´�? ������ "��"�����.
	
	//m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//WrieFrame���� �׷��ִ°�.

	//m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		

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

	m_pDX9_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//for (auto& renderer : m_RenderingList[3])
	//{
	//	renderer->Render();
	//}

	UIManager::Get_Instance()->Render();
		
#pragma region Test
	//IDirect3DBaseTexture9* temp = ResourceManager::Get_Instance()->Get_Resource<Texture>(L"PangDongE")->Get_Texture(0);
	//LPDIRECT3DTEXTURE9 temp2 = 
	//m_pDX9_Sprite->Draw(
	//	(LPDIRECT3DCUBETEXTURE9)(*temp),
	//	nullptr,
	//	nullptr,
	//	&Vector3(640.f,360.f, 1.f),
	//	D3DCOLOR_ARGB(255, 255, 255, 255))

	//IDirect3DBaseTexture9* temp = ResourceManager::Get_Instance()->Get_Resource<Texture>(L"HitEffect")->Get_Texture(0);
	//m_pTexture = (LPDIRECT3DTEXTURE9)temp;

	//Matrix matTemp, matScale, matTrans;
	//D3DXMatrixIdentity(&matTemp);

	//D3DXMatrixTranslation(&matTrans, 100, 500, 0 );
	//
	//matTemp = matTrans;

	//m_pDX9_Sprite->SetTransform(&matTemp);

	//Vector3 vTest = { 0.5f, 0.5f, 1.f };
	//if (FAILED(m_pDX9_Sprite->Draw(
	//	m_pTexture,
	//	nullptr,
	//	&Vector3(640.f, 360.f,0.f),
	//	nullptr,
	//	//&Vector3(640.f, 360.f, 0.f), //1�Ǹ� �����麸�� �ڿ� ����.
	//	D3DCOLOR_ARGB(255, 255, 255, 255))))
	//{
	//	assert(0 && L"sprite draw failed");
	//}

	int iFps = TimeManager::Get_Instance()->Get_FPS();

	wstring temp = L"FPS : " + to_wstring(iFps);
	RECT	RectTemp = { 0,0,0,0 };

	m_pTempFont->DrawTextW(
		nullptr,
		temp.c_str(), -1,
		&RectTemp, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
#pragma endregion
	m_pDX9_Sprite->End();
}

void RenderManager::Clear_RenderingList()
{
	m_RenderingList.clear();
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
		D3DCOLOR_ARGB(255, 255, 222, 222), 1.f, 0);

	m_pDX9_Device_DEBUG->BeginScene();


	/*	Debug Rendering	*/




	m_pDX9_Device_DEBUG->EndScene();

	m_pDX9_Device_DEBUG->Present(0, 0, 0, 0);

}
#endif //_DEBUG


