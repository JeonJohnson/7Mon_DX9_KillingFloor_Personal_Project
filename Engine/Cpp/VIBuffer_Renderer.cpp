#include "..\Header\VIBuffer_Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Texture.h"

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

	if (m_pVIBuffer->Get_Kind() == VIBUFFER_KIND::VIBuffer_Textrue)
	{
		Texture* TexTemp = ResourceManager::Get_Instance()->Get_Resource<Texture>(_desc->wTextureName);
		m_pVIBuffer->Set_Texture(TexTemp);
	}
	
}

VIBuffer_Renderer::~VIBuffer_Renderer()
{
}

void VIBuffer_Renderer::Initialize()
{
	///*Test*/
	//D3DXMatrixLookAtLH(&m_matView, &Vector3(0.f, 0.f, -10.f), &Vector3(0.f, 0.f, 1.f), &Vector3(0.f, 1.f, 0.f));
	//D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(60.f), float(1280) / 720, 0.1f, 1000.f);
}

void VIBuffer_Renderer::Update()
{
}

void VIBuffer_Renderer::LateUpdate()
{
}

void VIBuffer_Renderer::Render()
{
	

	m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());

	if (FAILED(Binding_Stream_VIBuffer()))
	{
		assert(0 && L"VIBuffer Binding Stream is Failed");
	}
		
	m_pVIBuffer->Render_Texture(0);

	if (m_pVIBuffer->Get_IBuffer_Com() == nullptr)
	{
		if (FAILED(m_pDX9_Device->DrawPrimitive(
			m_pVIBuffer->Get_DrawType(), //�׸������ϴ� ���, �ð�������� �ﰢ���� �׸��ڴ�.
			0, //���ؽ� �б⸦ ������ ���ؽ� ��Ʈ�� ����� �ε���
			m_pVIBuffer->Get_VBuffer_Info().m_iPolyCount //�׸� ����.
		)))
		{
			assert(0 && L"Vertex Buffer Object Draw Failed");
		}//VBuffer�� �̿��ؼ� �׸��°�
	}
	else 
	{
		if (FAILED(m_pDX9_Device->DrawIndexedPrimitive(
			m_pVIBuffer->Get_DrawType(), //�׸������ϴ� ���.
			0, 0,
			m_pVIBuffer->Get_VBuffer_Info().m_iVertexCount, //������ ����
			0,
			m_pVIBuffer->Get_VBuffer_Info().m_iPolyCount //�׸� �⺻���� ����.
		)))
		{
			assert(0 && L"Index Buffer Object Draw Failed");
		}
	}

	m_pDX9_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	
}


void VIBuffer_Renderer::Release()
{
}

HRESULT VIBuffer_Renderer::Binding_Stream_VIBuffer()
{
	if (FAILED(m_pDX9_Device->SetStreamSource(
		0,
		m_pVIBuffer->Get_VBuffer_Com(),
		0,
		m_pVIBuffer->Get_VBuffer_Info().m_iVertexMemSize)))
	{
		return E_FAIL;
	}

	if(FAILED(m_pDX9_Device->SetFVF(m_pVIBuffer->Get_VBuffer_Info().m_iFVF)))
	{
		return E_FAIL;
	}

	if (m_pVIBuffer->Get_IBuffer_Com() != nullptr)
	{
		if (FAILED(m_pDX9_Device->SetIndices(m_pVIBuffer->Get_IBuffer_Com())))
		{
			return E_FAIL;
		}
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



