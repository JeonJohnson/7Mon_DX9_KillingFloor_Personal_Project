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
	//�� Renderer�� �ִ� iLayer�� �������ְ�.
	//Rednerer���� �˾Ƽ� RenderManager�� ������ ^^~

	
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
	//	D3DPT_TRIANGLELIST //�׸������ϴ� ���, �ð�������� �ﰢ���� �׸��ڴ�.
	//	0, //���ؽ� �б⸦ ������ ���ؽ� ��Ʈ�� ����� �ε���
	//	1 //�׸� ����.
	//); VBuffer�� �̿��ؼ� �׸��°�

	if (FAILED(m_pDX9Device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, //�׸������ϴ� ���.
		0, 0,
		m_pVIBuffer->Get_VBuffer_Info().m_iVertexCount, //������ ����
		0,
		m_pVIBuffer->Get_VBuffer_Info().m_iPolyCount //�׸� �⺻���� ����.
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



