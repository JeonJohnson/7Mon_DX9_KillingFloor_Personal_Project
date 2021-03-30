#include "..\Header\VIBuffer_Renderer.h"
#include "ResourceManager.h"
//#include "Triangle_VIBuffer_Color.h"
//#include "Rect_VIBuffer_Color.h"



VIBuffer_Renderer::VIBuffer_Renderer(Desc * _desc)
{
	/* Test */
	//m_pVIBuffer = new Triangle_VIBuffer_Color;
	//m_pVIBuffer = new Rect_VIBuffer_Color;
	m_pVIBuffer = ResourceManager::Get_Instance()->Get_Resource<VIBuffer>(_desc->wBufferName);
	assert(L"VIBufferRenderer is cant find Obj" && m_pVIBuffer);
	m_pVIBuffer->Set_RenderLayer(_desc->iLayer);
	//거 Renderer에 있는 iLayer를 세팅해주고.
	//Rednerer에서 알아서 RenderManager로 보내줌 ^^~

	
}

VIBuffer_Renderer::~VIBuffer_Renderer()
{
}

void VIBuffer_Renderer::Initialize()
{
}

void VIBuffer_Renderer::Update()
{
}

void VIBuffer_Renderer::LateUpdate()
{
}

void VIBuffer_Renderer::Render()
{
	if (FAILED(Binding_Stream_VIBuffer()))
	{
		assert(0 && L"VIBuffer Binding Stream is Failed");
	}

	//m_pDX9Device->DrawPrimitive(
	//	D3DPT_TRIANGLELIST //그리고자하는 방식, 시계방향으로 삼각형을 그리겠다.
	//	0, //버텍스 읽기를 시작할 버텍스 스트림 요소의 인덱스
	//	1 //그릴 개수.
	//); VBuffer만 이용해서 그리는거

	if (FAILED(m_pDX9Device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, //그리고자하는 방식.
		0, 0,
		m_pVIBuffer->Get_VBuffer_Info().m_iVertexCount, //정점의 개수
		0,
		m_pVIBuffer->Get_VBuffer_Info().m_iPolyCount //그릴 기본형의 개수.
	)))
	{
		assert(0 && L"VIBuffer Object Draw Failed");
	}
}


void VIBuffer_Renderer::Release()
{
}

HRESULT VIBuffer_Renderer::Binding_Stream_VIBuffer()
{
	if (FAILED(m_pDX9Device->SetStreamSource(
		0,
		m_pVIBuffer->Get_VBuffer_Com(),
		0,
		m_pVIBuffer->Get_VBuffer_Info().m_iVertexMemSize)))
	{
		return E_FAIL;
	}

	if(FAILED(m_pDX9Device->SetFVF(m_pVIBuffer->Get_VBuffer_Info().m_iFVF)))
	{
		return E_FAIL;
	}

	if (FAILED(m_pDX9Device->SetIndices(m_pVIBuffer->Get_IBuffer_Com())))
	{
		return E_FAIL;
	}

	return S_OK;
}

VIBuffer * VIBuffer_Renderer::Get_VIBuffer() const
{
	return m_pVIBuffer;
}

void VIBuffer_Renderer::Set_VIBuffer(const wstring & _wBufferName)
{

}



