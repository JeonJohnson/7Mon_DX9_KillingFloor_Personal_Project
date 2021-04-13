#include "..\Header\Mesh_Renderer.h"

#include "StaticMesh.h"
#include "GameObject.h"
#include "ResourceManager.h"

Mesh_Renderer::Mesh_Renderer(Desc * _desc)
{
	//m_pStaticMesh = new StaticMesh;

	//m_pStaticMesh->Insert_StaticMesh(L"Test/StaticMesh/PoliceCar.X",
	//	L"Test/StaticMesh/LondonPoliceDiffuseDDS.png");

	m_pStaticMesh = ResourceManager::Get_Instance()->Get_Resource<StaticMesh>(_desc->szMeshName);


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
	m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());

	for (int i = 0; i < (int)m_pStaticMesh->Get_MaterialCount(); ++i)
	{
		m_pStaticMesh->Render_Texture(i);

		m_pStaticMesh->Get_Mesh()->DrawSubset(i);
	}
}

void Mesh_Renderer::Release()
{
}
