#include "..\Header\MeshRenderer.h"

#include "StaticMesh.h"
#include "GameObject.h"

MeshRenderer::MeshRenderer(Desc * _desc)
{
	m_pStaticMesh = new StaticMesh;

	m_pStaticMesh->Insert_StaticMesh(L"Test/StaticMesh/PoliceCar.X",
		L"Test/StaticMesh/LondonPoliceDiffuseDDS.png");
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Initialize()
{
}

void MeshRenderer::Update()
{
}

void MeshRenderer::LateUpdate()
{
}

void MeshRenderer::Render()
{

	m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());

	for (int i = 0; i < (int)m_pStaticMesh->Get_MaterialCount(); ++i)
	{
		m_pStaticMesh->Render_Texture(i);

		m_pStaticMesh->Get_Mesh()->DrawSubset(i);
	}
}

void MeshRenderer::Release()
{
}
