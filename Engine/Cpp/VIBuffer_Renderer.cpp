#include "..\Header\VIBuffer_Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Texture.h"
#include "DeviceManager.h"

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
	m_pVIBuffer->Set_RenderLayer(_desc->iLayer);
	//거 Renderer에 있는 iLayer를 세팅해주고.
	//Rednerer에서 알아서 RenderManager로 보내줌 ^^~

	if (m_pVIBuffer->Get_Kind() == VIBUFFER_KIND::VIBuffer_Textrue)
	{
		Texture* TexTemp = ResourceManager::Get_Instance()->Get_Resource<Texture>(_desc->wTextureName);
		m_pVIBuffer->Set_Texture(TexTemp);
	}
	
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
	Setup_ShaderTable();

	//m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());
	//m_pVIBuffer->Render_Texture(0); //저기 Setup_ShaderTable에서 해줌.
	//쉐이더 사용하면서 이걸 이제 쉐이더장치(m_pEffect에 맡길꺼임.)


	UINT	uiMaxPass = 0;
	m_pEffectCom->Begin(&uiMaxPass, 0);
	//Begine 첫번째 인자 -> 현재 쉐이더 파일이 지닌 최대 패스의 개수반환
	//		두번째 인자 -> 시작하는 방식을 묻는 인자, 0 = default
	m_pEffectCom->BeginPass(0);

	//렌더링 부분
	if (FAILED(Binding_Stream_VIBuffer()))
	{
		assert(0 && L"VIBuffer Binding Stream is Failed");
	}

	if (m_pVIBuffer->Get_IBuffer_Com() == nullptr)
	{
		if (FAILED(m_pDX9_Device->DrawPrimitive(
			m_pVIBuffer->Get_DrawType(), //그리고자하는 방식, 시계방향으로 삼각형을 그리겠다.
			0, //버텍스 읽기를 시작할 버텍스 스트림 요소의 인덱스
			m_pVIBuffer->Get_VBuffer_Info().m_iPolyCount //그릴 개수.
		)))
		{
			assert(0 && L"Vertex Buffer Object Draw Failed");
		}//VBuffer만 이용해서 그리는거
	}
	else 
	{
		m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		if (FAILED(m_pDX9_Device->DrawIndexedPrimitive(
			m_pVIBuffer->Get_DrawType(), //그리고자하는 방식.
			0, 0,
			m_pVIBuffer->Get_VBuffer_Info().m_iVertexCount, //정점의 개수
			0,
			m_pVIBuffer->Get_VBuffer_Info().m_iPolyCount //그릴 기본형의 개수.
		)))
		{
			assert(0 && L"Index Buffer Object Draw Failed");
		}
		m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	m_pEffectCom->EndPass();
	m_pEffectCom->End();

	//m_pDX9_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	
}


void VIBuffer_Renderer::Release()
{
	Safe_Delete(m_pShaderCom);
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

	m_pVIBuffer->Render_Texture(m_pEffectCom, "g_texBaseTexture", 0);

	return S_OK;
}

VIBuffer * VIBuffer_Renderer::Get_VIBuffer() const
{
	return m_pVIBuffer;
}

void VIBuffer_Renderer::Set_VIBuffer(const wstring & _wBufferName)
{
	
}



