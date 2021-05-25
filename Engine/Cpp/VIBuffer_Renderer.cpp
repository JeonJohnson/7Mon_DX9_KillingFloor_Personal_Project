#include "..\Header\VIBuffer_Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Texture.h"
#include "DeviceManager.h"
#include "TimeManager.h"
//#include "Triangle_VIBuffer_Color.h"
//#include "Rect_VIBuffer_Color.h"



VIBuffer_Renderer::VIBuffer_Renderer(Desc * _desc)
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"VIBuffer_Renderer is null" && m_pDX9_Device);
	
	
	/* Test */
	//m_pVIBuffer = new Triangle_VIBuffer_Color;
	//m_pVIBuffer = new Rect_VIBuffer_Color;
	m_pVIBuffer = ResourceManager::Get_Instance()->Get_Resource<VIBuffer>(_desc->wBufferName);
	assert(L"VIBufferRenderer is cant find Obj" && m_pVIBuffer);
	//m_pVIBuffer->Set_RenderLayer(_desc->iLayer);
	m_iRenderLayer = _desc->iLayer;
	//�� Renderer�� �ִ� iLayer�� �������ְ�.
	//Rednerer���� �˾Ƽ� RenderManager�� ������ ^^~

	if (m_pVIBuffer->Get_Kind() == VIBUFFER_KIND::VIBuffer_Textrue)
	{
		m_pTextureName = _desc->wTextureName;
		Texture* TexTemp = ResourceManager::Get_Instance()->Get_Resource<Texture>(m_pTextureName);
		m_pVIBuffer->Set_Texture(TexTemp);
	}
	
	m_bAlpha_Add = _desc->bAlpha_Add;
	m_bAlpha_Min = _desc->bEffect_Min;

	m_bFade = _desc->bFade;
	m_fFadeSpd = _desc->fFadeSpd;
	Create_Shader(_desc->szShaderName);

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


	if (m_pVIBuffer->Get_Kind() == VIBUFFER_KIND::VIBuffer_Textrue)
	{
		Texture* TexTemp = ResourceManager::Get_Instance()->Get_Resource<Texture>(m_pTextureName);
		m_pVIBuffer->Set_Texture(TexTemp);
	}

	if (m_bFade)
	{
		m_fAlpha += Engine_fTime * m_fFadeSpd;
	}
	Setup_ShaderTable();

	//m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());
	//m_pVIBuffer->Render_Texture(0); //���� Setup_ShaderTable���� ����.
	//���̴� ����ϸ鼭 �̰� ���� ���̴���ġ(m_pEffect�� �ñ沨��.)


	UINT	uiMaxPass = 0;
	m_pEffectCom->Begin(&uiMaxPass, 0);
	//Begine ù��° ���� -> ���� ���̴� ������ ���� �ִ� �н��� ������ȯ
	//		�ι�° ���� -> �����ϴ� ����� ���� ����, 0 = default
	m_pEffectCom->BeginPass(0);


	//������ �κ�
	if (FAILED(Binding_Stream_VIBuffer()))
	{
		assert(0 && L"VIBuffer Binding Stream is Failed");
	}

	if (m_pVIBuffer->Get_Kind() == VIBUFFER_KIND::VIBuffer_Textrue)
	{
		m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	else if (m_pVIBuffer->Get_Kind() == VIBUFFER_KIND::VIBuffer_Color)
	{
		m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	
	if (m_bAlpha_Add)
	{
		m_pDX9_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD);
		m_pDX9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE);
		m_pDX9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE);
	}
	else if (m_bAlpha_Min)
	{
		m_pDX9_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_MIN);

		m_pDX9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCCOLOR);
		m_pDX9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_DESTCOLOR);
		//m_pDX9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE);
		//m_pDX9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE);
	}
	else 
	{
		m_pDX9_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD);
		m_pDX9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA);
		m_pDX9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);
	}

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


	m_pDX9_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD);
	m_pDX9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA);
	m_pDX9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);

	m_pEffectCom->EndPass();
	m_pEffectCom->End();

	//m_pDX9_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}


void VIBuffer_Renderer::Release()
{
	//Safe_Delete(m_pShaderCom);
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

HRESULT VIBuffer_Renderer::Create_Shader(const wstring & _szShaderName)
{
	m_pShaderCom = ResourceManager::Get_Instance()->Get_Resource<Shader>(_szShaderName);
	assert(L"shader Load Failed at VIBufferRenderer"&& m_pShaderCom);

	if (m_pShaderCom == nullptr)
	{
		return E_FAIL;
	}

	m_pEffectCom = m_pShaderCom->Get_EffectCom();
	assert(L"EffectCom Load Failed at VIBufferRenderer"&& m_pEffectCom);

	
	return S_OK;
}

HRESULT VIBuffer_Renderer::Setup_ShaderTable()
{
	Matrix		matWorld, matView, matProj;

	matWorld = m_Transform->Get_WorldMatrix();
	m_pDX9_Device->GetTransform(D3DTS_VIEW, &matView);
	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &matProj);

	m_pEffectCom->SetMatrix("g_matWorld", &matWorld);
	m_pEffectCom->SetMatrix("g_matView", &matView);
	m_pEffectCom->SetMatrix("g_matProjection", &matProj);

	if (m_bFade)
	{
		m_pEffectCom->SetFloat("g_fAlpha", m_fAlpha);
	}
	
	m_pVIBuffer->Render_Texture(m_pEffectCom, "g_texBaseTexture", m_iTextureIndex);

	return S_OK;
}

VIBuffer * VIBuffer_Renderer::Get_VIBuffer() const
{
	return m_pVIBuffer;
}

int VIBuffer_Renderer::Get_TextureCount()
{
	return 0;
}

void VIBuffer_Renderer::Set_VIBuffer(const wstring & _wBufferName)
{
	
}

//void VIBuffer_Renderer::Set_Texture(Texture * _pTexture)
//{
//}

void VIBuffer_Renderer::Set_TextureIndex(int _iIndex)
{
	m_iTextureIndex = _iIndex;
}



