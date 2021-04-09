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
		tFontInfo.Weight = FW_SEMIBOLD; // 두께
		//tFontInfo.CharSet = HANGEUL_CHARSET; //한글폰트일때만
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
	//도형에 색깔이 안나온다? 조명을 "꺼"줘야함.
	
	//m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//WrieFrame으로 그려주는것.

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
	//	//&Vector3(640.f, 360.f, 0.f), //1되면 옵젝들보다 뒤에 있음.
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
	//렌더링 파이프라인
	/*
		1. 로컬 스페이스 : 각 오브젝트들의 자체 포지션 => 정점, 매쉬 
			(월드 행렬)↓ => 각 오브젝트,컴포넌트의 transform내에서 설정.
		2. 월드 스페이스 : 로칼 스페이스를 월드오 옮긴 것. 
			(뷰 행렬)↓ => 카메라에서 설정.
		3. 뷰 스페이스 : 월드 스페이스를 (0,0,0) / z양의방향을 바라보는 카메라 기준으로 바꾸는것.
		4. 조명 연산 : 
		5. 컬링 : 
			(투영 행렬)↓ => 카메라에서 설정.
		6. 프로젝션(투영) 스페이스 : 3D상의 물체들을 2D스크린에 출력하기 위한 단계.
			-> 시야각, 화면비율대로 맞춰주고 
			-> near와 far평면으로 z나누기를 해줌.
		7. 클리핑 : 
			(뷰 포트 설정)↓ => RenderManager에서 해줄 예정.
		8. 뷰 포트 : 렌더링 될 범위를 설정해주는것.
		9. 레스터라이즈 : 
	*/
	D3DVIEWPORT9	tViewPort;
	tViewPort.X = 0; //화면의 시작 X좌표 
	tViewPort.Y = 0; //화면의 시작 Y좌표
	tViewPort.Width = (DWORD)DeviceManager::Get_Instance()->Get_WindowSize().x; //해상도x
	tViewPort.Height = (DWORD)DeviceManager::Get_Instance()->Get_WindowSize().y; //해상도y
	tViewPort.MinZ = 0.f; //Z버퍼 최소
	tViewPort.MaxZ = 1.f; //Z버퍼 최대

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


