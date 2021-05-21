#include "..\Header\Mesh_Renderer.h"

//#include "StaticMesh.h"
//#include "AnimMesh.h"
#include "Mesh.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"
#include "LightManager.h"
#include "AnimationController.h"

Mesh_Renderer::Mesh_Renderer(Desc * _desc)
{
	if (_desc->szMeshName != L"")

	{
		m_pMesh = ResourceManager::Get_Instance()->Get_Resource<Mesh>(_desc->szMeshName);
		assert(L"AnimMesh Loading Failed" && m_pMesh);
	}

	//크기 //회전 // 이동 순서

	Matrix matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, _desc->vScale.x, _desc->vScale.y, _desc->vScale.z);
	
	D3DXMatrixRotationYawPitchRoll(&matRot,
		D3DXToRadian(_desc->vRot.y), D3DXToRadian(_desc->vRot.x), D3DXToRadian(_desc->vRot.z));
	
	D3DXMatrixTranslation(&matTrans, _desc->vPos.x, _desc->vPos.y, _desc->vPos.z);

	m_matMeshTransform = matScale * matRot * matTrans;

	//m_matMeshMatrix = _desc->matMeshMatrix;
	//if (m_pMesh->Get_AnimationController() != nullptr)
	//{
	//	m_pMesh->Set_AnimationSet(_desc->iAnimIndex);
	//}

	m_iRenderLayer = _desc->iRenderLayer;

	Create_Shader(_desc->szShaderName);
}

Mesh_Renderer::~Mesh_Renderer()
{
}

void Mesh_Renderer::Initialize()
{
}

void Mesh_Renderer::Update()
{
}

void Mesh_Renderer::LateUpdate()
{
}

void Mesh_Renderer::Render()
{
	//Device Rendering
		//m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());
	
	//Shader Rendering
	Setup_ShaderTable();
	
	unsigned int uiMaxPass = 0;

	m_pEffectCom->Begin(&uiMaxPass, 0);
	m_pEffectCom->BeginPass(0);


	m_pDX9_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//Render Function
	if (m_pMesh->Get_AnimController() == nullptr)
	{//StaticMesh Rendering
#pragma region Olds
	 //D3DXFRAME안의 메시컨테이너 안에 매쉬정보들 있음.
		//for (int i = 0; i < (int)m_pStaticMesh->Get_MaterialCount(); ++i)
		//{
		//	m_pStaticMesh->Render_Texture(i);
					//=> m_pDX9_Device->SetTexture(0, m_pTexture->Get_Texture(_iNum))
		//	m_pStaticMesh->Get_Mesh()->DrawSubset(i);
		//}
		//MeshContainer_Derived* temp = m_pMesh->Get_RootFrame_MeshContainer();
		//	 
		//assert(L"MeshContainer_Derived is nullptr" && temp);

		//Texture* tempTexture = temp->pTexture;

		//for (int i = 0; i < (int)m_pMesh->Get_RootFrame()->pMeshContainer->NumMaterials; ++i)
		//{
		//	//왜 pMesh 접근을 못할까 이 씹새끼는...?
		//	//왜 되지?
		//	if (FAILED(m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i))))
		//	{
		//		assert(0 && L"SetTexture Faild at Static Mesh Renderring");
		//	}
		//	if (FAILED(temp->MeshData.pMesh->DrawSubset(i)))
		//	{
		//		assert(0 && L"DrawSubSet Failed at Static Mesh Renderring");
		//	}
		//}
#pragma	endregion
		for (auto& iter : m_pMesh->Get_MeshContainerList())
		{
			D3DXMESHCONTAINER_DERIVED* pMeshContainer = iter;
			Texture*	tempTexture = pMeshContainer->pTexture;

			for (int i = 0; i < (int)pMeshContainer->NumMaterials; ++i)
			{
				//if (FAILED(m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i))))
				//{
				//	assert(0 && L"SetTexture Faild at Static Mesh Renderring");
				//}
				HRESULT TexResult = m_pEffectCom->SetTexture("g_texBaseTexture", tempTexture->Get_Texture(i));
				if (TexResult == E_FAIL)
				{	assert(0 && L"SetTexture Faild at Static Mesh Renderring");
				}
				m_pEffectCom->CommitChanges();
					
				if (FAILED(iter->MeshData.pMesh->DrawSubset(i)))
				{
					assert(0 && L"DrawSubSet Failed at Static Mesh Renderring");
				}
			}
		}
	}
	else
	{//Dynamic Mesh
		
		Animating();
		

		for (auto& iter : m_pMesh->Get_MeshContainerList())
		{
			D3DXMESHCONTAINER_DERIVED*		pMeshContainer = iter;
			Texture* tempTexture = pMeshContainer->pTexture;

			for (int i = 0; i < pMeshContainer->iBoneCount; ++i)
			{
				pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppCombinedTrasnformMatrix[i]);
			}
			void*		pSrcVtx = nullptr;
			void*		pDestVtx = nullptr;
			pMeshContainer->pOriginMesh->LockVertexBuffer(0, &pSrcVtx);
			pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);
			// 소프트 웨어 스키닝을 수행하는 함수
			//(스키닝 뿐 아니라 애니메이션 변경 시, 뼈들과 정점 정보들의 변경 또한 동시에 수행해 줌)
			pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->pRenderingMatrix, NULL, pSrcVtx, pDestVtx);
			
			for (DWORD i = 0; i < pMeshContainer->NumMaterials; ++i)
			{
				m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i));
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
			pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
			pMeshContainer->pOriginMesh->UnlockVertexBuffer();
		}
	}

	m_pEffectCom->EndPass();
	m_pEffectCom->End();

}

void Mesh_Renderer::Release()
{

}

void Mesh_Renderer::Create_Shader(const wstring& _szShaderName)
{
	//m_pShaderCom = new Shader;
	//m_pShaderCom->Ready_Shader(L"../../Reference/Shader/Shader_Mesh.fx");
	////나중에 이거 desc로 바꿔주기(ViBuffer Renderer도 )
	//m_pEffectCom = m_pShaderCom->Get_EffectCom();

	//assert(L"EffectCom is Nullptr" && m_pEffectCom);

	m_pShaderCom = ResourceManager::Get_Instance()->Get_Resource<Shader>(_szShaderName);
	m_pEffectCom = m_pShaderCom->Get_EffectCom();

	assert(L"EffectCom is Nullptr" && m_pEffectCom);
}

void Mesh_Renderer::Setup_ShaderTable()
{
	Matrix	matWorld, matView, matProjection;

	matWorld = m_Transform->Get_WorldMatrix();
	m_pDX9_Device->GetTransform(D3DTS_VIEW, &matView);
	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &matProjection);

	m_pEffectCom->SetMatrix("g_matWorld", &matWorld);
	m_pEffectCom->SetMatrix("g_matView", &matView);
	m_pEffectCom->SetMatrix("g_matProjection", &matProjection);

	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pEffectCom->SetVector("g_vCamPos", (Vector4*)&matView._41);
	//나중에 매인 캠 트랜스폼 받아오는거 Engine_Mother에 만들기.

	//조명 세팅
	D3DLIGHT9	TempLight;
	ZeroMemory(&TempLight, sizeof(D3DLIGHT9));
	TempLight= LightManager::Get_Instance()->Get_LightByName(L"SunShine")->Get_Light();

	m_pEffectCom->SetVector("g_vLightDir", &Vector4(TempLight.Direction, 0.f));
	m_pEffectCom->SetVector("g_vLightDiffuse", (Vector4*)&TempLight.Diffuse);
	m_pEffectCom->SetVector("g_vLightSpecular", (Vector4*)&TempLight.Specular);
	m_pEffectCom->SetVector("g_vLightAmbient", (Vector4*)&TempLight.Ambient);

	//
	D3DMATERIAL9				tMtrlInfo;
	ZeroMemory(&tMtrlInfo, sizeof(D3DMATERIAL9));
	tMtrlInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	tMtrlInfo.Power = 20.f;

	m_pEffectCom->SetVector("g_vMtrlDiffuse", (Vector4*)(&tMtrlInfo.Diffuse));
	m_pEffectCom->SetVector("g_vMtrlSpecular", (Vector4*)(&tMtrlInfo.Specular));
	m_pEffectCom->SetVector("g_vMtrlAmbient", (Vector4*)(&tMtrlInfo.Ambient));
	m_pEffectCom->SetFloat("g_fPower", tMtrlInfo.Power);


}

void Mesh_Renderer::Animating()
{
	auto AnimCtrl = m_GameObject->Get_Component<AnimationController>();

	if(AnimCtrl)
	{
		if (AnimCtrl->Get_Playing())
		{
			AnimCtrl->Animating();

			if (m_pMesh)
			{
				m_pMesh->Update_BoneMatrix((D3DXFrame_Derived*)(m_pMesh->Get_RootFrame()), &m_matMeshTransform);
			}

		}
	}

}

Mesh * Mesh_Renderer::Get_Mesh()
{
	return m_pMesh;
}

void Mesh_Renderer::Set_Mesh(Mesh * _pMesh)
{
	assert(L"pMesh is nullptr" && _pMesh);

	m_pMesh = _pMesh;
}

void Mesh_Renderer::Set_Mesh(const wstring & _pMeshName)
{
	m_pMesh = ResourceManager::Get_Instance()->Get_Resource<Mesh>(_pMeshName);
}
