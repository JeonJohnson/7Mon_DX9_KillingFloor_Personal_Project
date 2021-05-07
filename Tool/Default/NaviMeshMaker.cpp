#include "stdafx.h"
#include "NaviMeshMaker.h"
#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"
#include "Engine_Struct.h"

NaviMeshMaker::NaviMeshMaker(Desc * _desc)
{
}

NaviMeshMaker::~NaviMeshMaker()
{
}

void NaviMeshMaker::Initialize()
{
}

void NaviMeshMaker::Update()
{
	if (MouseUp(KEY_STATE_LMouse) && g_pNaviMeshTool_Dialog->m_bPointCreate)
	{
		if (KeyPress(KEY_STATE_LCtrl))
		{
			if (g_pDefaultView->m_tMousePos_View.x >= 0)
			{
				m_tMousePos.x = (FLOAT)g_pDefaultView->m_tMousePos_View.x;
				m_tMousePos.y = (FLOAT)g_pDefaultView->m_tMousePos_View.y;

				m_vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_tMousePos, 100);
				//m_vWorldPos.y = 0.f;

				Create_Ray(m_tMousePos);

				g_pNaviMeshTool_Dialog->Create_NaviPoint(m_vWorldPos);

			}
		}
		else
		{
			Picking(); 
		}

	}
}

void NaviMeshMaker::LateUpdate()
{

}

void NaviMeshMaker::ReadyRender()
{
}

void NaviMeshMaker::Release()
{
}

void NaviMeshMaker::Create_Point()
{
}

void NaviMeshMaker::Picking()
{
	auto naviPoints = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_NAVIPOINT);

	for (auto iter = naviPoints.begin(); iter != naviPoints.end();)
	{
		LPD3DXMESH temp = (*iter)->Get_Component<Mesh_Renderer>()
			->Get_Mesh()->Get_MeshContainerList().front()->pOriginMesh;
		assert(L"Mesh is nulptr at NaviMeshMaker" && temp);
		
		Matrix matWorld = (*iter)->Get_Transform()->Get_WorldMatrix();

		//temp->CloneMeshFVF(D3DXMESH_MANAGED, temp->GetFVF(),)
		LPDIRECT3DVERTEXBUFFER9 pVB;
		LPDIRECT3DINDEXBUFFER9 pIB;

		VERTEX_TEXTURE* pVertex;
		DWORD*			pIndex;

		temp->GetVertexBuffer(&pVB);
		temp->GetIndexBuffer(&pIB);

		pIB->Lock(0, 0, (void**)&pIndex, 0);
		pVB->Lock(0, 0, (void**)&pVertex, 0);

		float	fBary1, fBary2;
		float	fDist;

		for(UINT i = 0; i <temp->GetNumFaces(); ++i)
		{
			Vector3 v0 = pVertex[pIndex[3 * i + 0]].vPos;
			Vector3 v1 = pVertex[pIndex[3 * i + 1]].vPos;
			Vector3 v2 = pVertex[pIndex[3 * i + 2]].vPos;

			D3DXVec3TransformCoord(&v0, &v0, &matWorld);
			D3DXVec3TransformCoord(&v1, &v1, &matWorld);
			D3DXVec3TransformCoord(&v2, &v2, &matWorld);

			if (D3DXIntersectTri(&v0, &v1, &v2, &m_vRayOrigin, &m_vRayDir, &fBary1, &fBary2, &fDist))
			{
				int i = 0;
			}
		}


	}
}

Vector3 NaviMeshMaker::Create_Ray(const Vector2 & _ScreenPos)
{
	EngineFunction->Get_MainCamera()->Screen2World(_ScreenPos,0, &m_vRayOrigin, &m_vRayDir);

	return Vector3();
}

