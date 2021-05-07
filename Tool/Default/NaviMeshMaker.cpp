#include "stdafx.h"
#include "NaviMeshMaker.h"
#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"
#include "Engine_Struct.h"
#include "..\..\Engine\Header\DeviceManager.h"

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

				g_pNaviMeshTool_Dialog->Create_NaviPoint(m_vWorldPos);
			}
		}
		else
		{
			m_tMousePos.x = (FLOAT)g_pDefaultView->m_tMousePos_View.x;
			m_tMousePos.y = (FLOAT)g_pDefaultView->m_tMousePos_View.y;

			Create_Ray(m_tMousePos);

			float dist;
			Vector3	Intersection;
			wstring meshName;

			if (Picking_Ray2Sphere(&dist, &Intersection, &meshName))
			{
				int i = 0;
			}
			//Picking_Mesh(); 
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

void NaviMeshMaker::Picking_Mesh()
{
	//

	auto naviPoints = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_NAVIPOINT);

	for (auto iter = naviPoints.begin(); iter != naviPoints.end();)
	{
		LPD3DXMESH temp = (*iter)->Get_Component<Mesh_Renderer>()
			->Get_Mesh()->Get_MeshContainerList().front()->MeshData.pMesh;
		
		assert(L"Mesh is nulptr at NaviMeshMaker" && temp);

		LPD3DXMESH	pMeshClone = nullptr;

		temp->CloneMeshFVF(
			/*D3DXMESH_MANAGED,*/
			temp->GetOptions(),
			temp->GetFVF(),
			EngineFunction->Get_Dx9_Device(),
			&pMeshClone);

		assert(L"MeshClone is Falied at MeshMaker" && pMeshClone);
		
		Matrix matWorld = (*iter)->Get_Transform()->Get_WorldMatrix();

		//temp->CloneMeshFVF(D3DXMESH_MANAGED, temp->GetFVF(),)
		LPDIRECT3DVERTEXBUFFER9		pVB = nullptr;
		LPDIRECT3DINDEXBUFFER9		pIB = nullptr;

		//�� �Ž��� FVF�� �̰�������.
		//�׷��� �̷������� ��Ÿ�Ӷ� �ҷ��ö��
		//FVF�� �����ͼ� if������ ���ư��鼭 � ���� �ִ��� Ȯ���ؼ� �����.
		//�׷��� �ؿ������� ����
		//��Ÿ���߿� �̷������� �������°� ���ƴϰ�
		//�Ž��� �ε��ϸ鼭 �׳� �ƿ� Vertexbuffer������ IndexBuffer���� Pos���� ���� ��������
		//����ϰ� ���δ�. �̸�����.
		VERTEX_TEXTURE*					pVertex;
		DWORD*							pIndex;

		pMeshClone->GetVertexBuffer(&pVB);
		pMeshClone->GetIndexBuffer(&pIB);

		pIB->Lock(0, 0, (void**)&pIndex, 0);
		pVB->Lock(0, 0, (void**)&pVertex, 0);

		float	fBary1, fBary2;
		float	fDist;

		UINT	FaceCount = pMeshClone->GetNumFaces();

		for(UINT i = 0; i <FaceCount; ++i)
		{
			//int index = pIndex[3 * i + 0];

			//���ؽ� ���ۿ� ������ �ȵ�. �� ����.
			Vector3 v0 = pVertex[pIndex[i*3 + 0]].vPos;
			Vector3 v1 = pVertex[pIndex[i*3 + 1]].vPos;
			Vector3 v2 = pVertex[pIndex[i*3 + 2]].vPos;

			D3DXVec3TransformCoord(&v0, &v0, &matWorld);
			D3DXVec3TransformCoord(&v1, &v1, &matWorld);
			D3DXVec3TransformCoord(&v2, &v2, &matWorld);

			if (D3DXIntersectTri(&v0, &v1, &v2, 
				&m_vRayOrigin, &m_vRayDir, 
				&fBary1, &fBary2, &fDist))
			{
				int i = 0;
			}
		}

		pVB->Unlock();
		pIB->Unlock();


		/*
		Vector3* m_vertexPositionData = nullptr;
			INDEX32* m_indexData = nullptr;
		m_vertexPositionData = new Vector3[m_vertexCount];
			m_indexData = new INDEX32[m_figureCount];

			DWORD vertexIndex = 0;
			DWORD figureIndex = 0;

			for (auto& meshContainer : m_meshContainerList)
			{
				LPD3DXMESH mesh = meshContainer->MeshData.pMesh;

				D3DVERTEXELEMENT9            decl[MAX_FVF_DECL_SIZE];
				ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
				mesh->GetDeclaration(decl);
				DWORD offset = 0;

				for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; ++i)
				{
					if (decl[i].Usage == D3DDECLUSAGE_POSITION)
					{
						offset = (unsigned char)decl[i].Offset;
						break;
					}
				}

				void* vertexMem = nullptr;
				mesh->LockVertexBuffer(0, &vertexMem);
				DWORD currentVertexCount = mesh->GetNumVertices();
				for (DWORD i = 0; i < currentVertexCount; ++i)
				{
					m_vertexPositionData[vertexIndex] = ((Vector3)(((char*)vertexMem) + (m_stride * i + offset)));
					++vertexIndex;
				}
				mesh->UnlockVertexBuffer();


				void* indexMem = nullptr;
				mesh->LockIndexBuffer(0, &indexMem);
				DWORD currentFigureCount = mesh->GetNumFaces();
				for (DWORD i = 0; i < currentFigureCount; ++i)
				{
					m_indexData[figureIndex] = ((INDEX32*)indexMem)[i];
					++figureIndex;
				}
				//memcpy(&m_indexData[figureIndex], indexMem, sizeof(INDEX32) * currentFigureCount);
				mesh->UnlockIndexBuffer();
			}*/
	}
}

bool NaviMeshMaker::Picking_Ray2Sphere(float* _fpOutDistance, Vector3* _vpOutIntersection, 
	wstring* _szMeshName)
{
	auto naviPoints = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_NAVIPOINT);
	
#pragma region Test
	//Vector3		vSphereCenter;
	//float		fSphereRadius;
	//Vector3		vOrigin2Center;

	//Vector3		vInterectPoint = { 0.f, 0.f, 0.f };

	//float		fDistance;

	//for (auto& naviPoint : naviPoints)
	//{
	//	vSphereCenter = naviPoint->Get_Position();
	//	fSphereRadius = 2.f;

	//	//�� ���̰� ������ ���̺��� ª�� ��� ���� ���ο��� ��ŷ�ϴ°�.
	//	vOrigin2Center = m_vRayOrigin - vSphereCenter;
	//	
	//	//���� ����ģ ��� üũ�ϱ� ���ؼ� ����.
	//	float	fDotOrigin2Center = D3DXVec3Dot(&m_vRayOrigin, &m_vRayOrigin);
	//	float	fRadiusPow2 = pow(fSphereRadius, 2);

	//	//������ ����� ���������->������ �� ����		
	//	float fSameDir = D3DXVec3Dot(&m_vRayDir, &vOrigin2Center);
	//	
	//	//���� ������ ����
	//	float ���ǹ��������� = pow(fSphereRadius, 2);

	//	if (fSameDir < 0.f /*&& fDotOrigin2Center > fRadiusPow2*/)
	//	{	//ù ���� => ������ ����� 0�̸�(����)�̸� ���̴� ������ ���ݴ�(90~270�� ����)
	//		//�ι�° ���� => ���� ����ģ ���
	//		return false;
	//	}
	//	
	//	float	�����ǹ߰������ǰŸ����� = fDotOrigin2Center - pow(fSameDir, 2);

	//	if (�����ǹ߰������ǰŸ����� > ���ǹ���������)
	//	{//������ ���� ���ܰ��°��
	//		return false;
	//	}
	//	
	//	float q = sqrtf(���ǹ��������� - �����ǹ߰������ǰŸ�����);

	//	if (fDotOrigin2Center > ���ǹ���������)
	//	{
	//		fDistance = fSameDir - q;
	//	}
	//	else 
	//	{
	//		fDistance = fSameDir + q;
	//	}

	//	vInterectPoint = m_vRayOrigin + fDistance* m_vRayDir;

	//	if (_fpOutDistance != nullptr)
	//	{
	//		*_fpOutDistance = fDistance;
	//	}

	//	if (_vpOutIntersection != nullptr)
	//	{
	//		*_vpOutIntersection = vInterectPoint;
	//	}

	//	return true;
	//

	//}
#pragma endregion

	for (auto& naviPoint : naviPoints)
	{
		Vector3		vSphereCenter = naviPoint->Get_Position();
		float		fSphereRadius = 0.05f;

		Vector3 l = vSphereCenter - m_vRayOrigin;

		float fLength_L = D3DXVec3Length(&l);
		D3DXVec3Normalize(&l, &l);
	
		double s = D3DXVec3Dot(&l, &m_vRayDir);
		double l2 = D3DXVec3Dot(&l, &l);
		double r2 = pow(fSphereRadius, 2);

		if (s < 0 && l2 > r2)
		{
			return false;
		}

		double m2 = l2 - pow(s, 2);

		if (m2 > r2)
		{
			return false;
		}

		double q = sqrt(r2 - m2);

		float fDistance = 0;
		if (l2 > r2)
		{
			fDistance = (float)(s - q);
		}
		else
		{
			fDistance = (float)(s + q);
		}

		if (_fpOutDistance != nullptr)
		{	
			*_fpOutDistance = fDistance*fLength_L;
		}
		if (_vpOutIntersection != nullptr)
		{
			*_vpOutIntersection = m_vRayOrigin + fDistance*m_vRayOrigin;
		}

		if (_szMeshName != nullptr)
		{
			*_szMeshName = naviPoint->Get_Name();
		}

		return true;

	}
	return false;

}

void NaviMeshMaker::Create_Ray(const Vector2 & _ScreenPos)
{
#pragma region Failed
	//Vector2 PosTemp = _ScreenPos;

	//float wincx = EngineFunction->Get_WindowSize().x;
	//float wincy = EngineFunction->Get_WindowSize().y;
	//
	//////PosTemp.x = _ScreenPos.x / (wincx * 0.5f) - 1.f;
	//////PosTemp.y = _ScreenPos.y / (wincy * -0.5f) + 1.f;
	////PosTemp.x = ((2.f * _ScreenPos.x) / wincx) - 1.f;
	////PosTemp.y = ((-2.f * _ScreenPos.y) / wincy) + 1.f;

	/*�� �����̽� ������ ��ȯ.*/
	m_vRayOrigin = { 0.f,0.f,0.f }; //�佺���̽� ��ü�� ī�޶� �������� �ɢh���� ��ġ�ϴ°Ŷ�
	//���������� 0,0,0��
	EngineFunction->Get_MainCamera()->Screen2World(_ScreenPos,0, &m_vRayDir);
	//�Ÿ� 0�̶� �ᱹ �� ī�޶� ��ġ/RayOrigin�̶� ����.

	/* ���彺���̽� ��ȯ */
	Matrix invViewSpace;
	EngineFunction->Get_Dx9_Device()->GetTransform(D3DTS_VIEW, &invViewSpace);
	D3DXMatrixInverse(&invViewSpace, 0, &invViewSpace);
	//���� ������ ��ġ ����(w = 1)
	//=>TransformCoord
	D3DXVec3TransformCoord(&m_vRayOrigin, &m_vRayOrigin, &invViewSpace);

	//������ ���⺤��(w = 0)
	//=>TransformNormal
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &invViewSpace);
	//�븻���������.
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);	
	//
	////m_vRayDir = m_vRayOrigin + Temp;
#pragma endregion

	////������ �� 0,0,0 ���� ����� �Ѿ���� ī�޶� ��ġ��.
	//m_vRayOrigin = EngineFunction->Get_MainCamera()->Get_Transform()->Get_Position();

	//Vector2 ScreenPos = _ScreenPos;
	//Vector2 WindowSize = EngineFunction->Get_WindowSize();

	//LPDIRECT3DDEVICE9 device = EngineFunction->Get_Dx9_Device();
	//D3DVIEWPORT9	viewport;
	//device->GetViewport(&viewport);

	//Vector3 ProjecTrans;
	//ProjecTrans.x = ((2.f * ScreenPos.x)/viewport.Width) - 1.f;
	//ProjecTrans.y = ((-2.f * ScreenPos.y) / viewport.Height) + 1.f;
	//ProjecTrans.z = 1.f;

	//Matrix invProj;
	//device->GetTransform(D3DTS_PROJECTION, &invProj);
	//D3DXMatrixInverse(&invProj, 0, &invProj);
	//D3DXVec3TransformCoord(&m_vRayDir, &ProjecTrans, &invProj);
	//
	//Matrix invViewSpace;
	//device->GetTransform(D3DTS_VIEW, &invViewSpace);
	//D3DXMatrixInverse(&invViewSpace, 0, &invViewSpace);
	//D3DXVec3TransformCoord(&m_vRayDir, &m_vRayDir, &invViewSpace);



}

//static float GetDistance_PointToInfinityLine(const Vector3& P1, const Line& L1)
//{ //������ ������ �������� �Ÿ�
//	Vector3 AB = L1.end - L1.start;
//	Vector3 AP = P1 - L1.start;
//
//	float area = Nalmak_Math::Magnitude(Nalmak_Math::Cross(AB, AP));
//	float CD = area / Nalmak_Math::Magnitude(AB);
//
//	return CD;
//}
//�ű״�Ʃ�� : sqrtf(_value.x * _value.x + _value.y * _value.y + _value.z * _value.z);

//Vector3 center = render->GetTransform()->GetWorldPosition();
//{
//���а� ���� ������ �Ÿ�.
		//float rayDx = (endRayPos.x - startRayPos.x) / rayLength;
		//float rayDy = (endRayPos.y - startRayPos.y) / rayLength;
		//float rayDz = (endRayPos.z - startRayPos.z) / rayLength;

		//float t =
		//rayDx * (center.x - startRayPos.x) +
		//rayDy * (center.y - startRayPos.y) +
		//rayDz * (center.z - startRayPos.z);
//
		//float Ex = t * rayDx + startRayPos.x;
		//float Ey = t * rayDy + startRayPos.y;
		//float Ez = t * rayDz + startRayPos.z;
//
		//float LineToSphereMinDistance = pow(Ex - center.x, 2) + pow(Ey - center.y, 2) + pow(Ez - center.z, 2);
//}
