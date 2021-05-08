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

//ï¿½Ì°ï¿½ ï¿½×³ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½Ì¾ï¿½ ï¿½Î±ï¿½ ï¿½È¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½. ï¿½Ã¹ï¿½ ï¿½ï¿½ï¿½â¼­ ï¿½Ï´Ï±ï¿½ ï¿½Ê¹ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 
void NaviMeshMaker::Update()
{
	if (MouseUp(KEY_STATE_LMouse) && g_pNaviMeshTool_Dialog->m_bPointCreate)
	//if (MouseUp(KEY_STATE_LMouse) && g_pNaviMeshTool_Dialog->m_bPointCreate)
	//{
	//	if (KeyPress(KEY_STATE_LCtrl))
	//	{
	//		if (g_pDefaultView->m_tMousePos_View.x >= 0)
	//		{
	//			m_tMousePos.x = (FLOAT)g_pDefaultView->m_tMousePos_View.x;
	//			m_tMousePos.y = (FLOAT)g_pDefaultView->m_tMousePos_View.y;

	//			m_vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_tMousePos, 100);
	//			//m_vWorldPos.y = 0.f;

	//			g_pNaviMeshTool_Dialog->Create_NaviPoint(m_vWorldPos);
	//		}
	//	}
	//	else
	//	{
	//		m_tMousePos.x = (FLOAT)g_pDefaultView->m_tMousePos_View.x;
	//		m_tMousePos.y = (FLOAT)g_pDefaultView->m_tMousePos_View.y;

	//		Create_Ray(m_tMousePos);

	//		float dist;
	//		Vector3	Intersection;
	//		//wstring meshName;
	//		GameObject* Obj = nullptr;


	//		if (Picking_Ray2Sphere(&Obj, &dist, &Intersection))
	//		{
	//			Notice(L"Shpere Picking is succed");
	//			g_pNaviMeshTool_Dialog->Create_NaviPoint(m_vWorldPos,Obj);
	//		}
	//		else 
	//		{
	//			Notice(L"Shpere Picking is falied");
	//		}
	//		//Picking_Mesh(); 
	//	}

	//}
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

		//ÀÌ ¸Å½¬ÀÇ FVF°¡ ÀÌ°ÅÀÎÁö¸ð¸§.
		//±×·¡¼­ ÀÌ·±½ÄÀ¸·Î ·±Å¸ÀÓ¶§ ºÒ·¯¿Ã¶ó¸é
		//FVF¸¦ °¡Á®¿Í¼­ if¹®À¸·Î µ¹¾Æ°¡¸é¼­ ¾î¶² °ªÀÌ ÀÖ´ÂÁö È®ÀÎÇØ¼­ ½á¾ßÇÔ.
		//±×·¡¼­ ÁØ¿±ÀÌÇÜÀÇ ²ÜÆÁ
		//·±Å¸ÀÓÁß¿¡ ÀÌ·±½ÄÀ¸·Î °¡Á®¿À´Â°Ç ¿µ¾Æ´Ï°í
		//¸Å½¬¸¦ ·ÎµåÇÏ¸é¼­ ±×³É ¾Æ¿¹ VertexbufferÁ¤º¸¶û IndexBuffer¿¡¼­ Pos°ª¸¸ µû·Î »©³õÀ¸¸é
		//¿ä±äÇÏ°Ô ¾²ÀÎ´Ù. ÀÌ¸¶¸®¾ß.
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

			//¹öÅØ½º ¹öÆÛ¿¡ Á¢±ÙÀÌ ¾ÈµÊ. °³ ¾¾¹ß.
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

bool NaviMeshMaker::Picking_Ray2Sphere(GameObject** _PickingOjbect,
	float* _fpOutDistance,
	Vector3* _vpOutIntersection)
{

	auto naviPoints = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_NAVIPOINT);
	
	vector<GameObject*>		vecPickObj;
	vector<float>			vecDistance;
	vector<Vector3>			vecIntersection;

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

	//	//ÀÌ ±æÀÌ°¡ ÁßÁ¡ÀÇ ±æÀÌº¸´Ù ÂªÀ» °æ¿ì ±¸ÀÇ ³»ºÎ¿¡¼­ ÇÇÅ·ÇÏ´Â°Í.
	//	vOrigin2Center = m_vRayOrigin - vSphereCenter;
	//	
	//	//±¸¸¦ Áö³ªÄ£ °æ¿ì Ã¼Å©ÇÏ±â À§ÇØ¼­ ¸¸µê.
	//	float	fDotOrigin2Center = D3DXVec3Dot(&m_vRayOrigin, &m_vRayOrigin);
	//	float	fRadiusPow2 = pow(fSphereRadius, 2);

	//	//·¹ÀÌÀÇ ¹æÇâ°ú ·¹ÀÌÃâ¹ßÁ¡->±¸¿øÁ¡ À» ³»Àû		
	//	float fSameDir = D3DXVec3Dot(&m_vRayDir, &vOrigin2Center);
	//	
	//	//±¸ÀÇ ¹ÝÁö¸§ Á¦°ö
	//	float ±¸ÀÇ¹ÝÁö¸§Á¦°ö = pow(fSphereRadius, 2);

	//	if (fSameDir < 0.f /*&& fDotOrigin2Center > fRadiusPow2*/)
	//	{	//Ã¹ Á¶°Ç => ³»ÀûÀÇ °á°ú°¡ 0¹Ì¸¸(À½¼ö)ÀÌ¸é ·¹ÀÌ´Â ¹æÇâÀÌ Á¤¹Ý´ë(90~270µµ »çÀÌ)
	//		//µÎ¹øÂ° Á¶°Ç => ±¸¸¦ Áö³ªÄ£ °æ¿ì
	//		return false;
	//	}
	//	
	//	float	¼ö¼±ÀÇ¹ß°ú·¹ÀÌÀÇ°Å¸®Á¦°ö = fDotOrigin2Center - pow(fSameDir, 2);

	//	if (¼ö¼±ÀÇ¹ß°ú·¹ÀÌÀÇ°Å¸®Á¦°ö > ±¸ÀÇ¹ÝÁö¸§Á¦°ö)
	//	{//±¤¼±ÀÌ ±¸¸¦ ºø°Ü°¡´Â°æ¿ì
	//		return false;
	//	}
	//	
	//	float q = sqrtf(±¸ÀÇ¹ÝÁö¸§Á¦°ö - ¼ö¼±ÀÇ¹ß°ú·¹ÀÌÀÇ°Å¸®Á¦°ö);

	//	if (fDotOrigin2Center > ±¸ÀÇ¹ÝÁö¸§Á¦°ö)
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
			//return false;
			continue;
		}

		double m2 = l2 - pow(s, 2);

		if (m2 > r2)
		{
			//return false;
			continue;
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
		vecDistance.emplace_back(fDistance * fLength_L);
		vecIntersection.emplace_back(m_vRayOrigin + fDistance*m_vRayDir);
		vecPickObj.emplace_back(naviPoint);


		//if (_fpOutDistance != nullptr)
		//{	
		//	*_fpOutDistance = fDistance*fLength_L;
		//}
		//if (_vpOutIntersection != nullptr)
		//{
		//	*_vpOutIntersection = m_vRayOrigin + fDistance*m_vRayDir;
		//}

		//if (_szMeshName != nullptr)
		//{
		//	*_szMeshName = naviPoint->Get_Name();
		//}

		//return true;
	}

	if (vecPickObj.size() == 0)
	{
		return false;
	}

	if (vecPickObj.size() == 1)
	{
		*_PickingOjbect = vecPickObj.front();
		*_fpOutDistance = vecDistance.front();
		*_vpOutIntersection = vecIntersection.front();

		return true;
	}

	if (vecPickObj.size() > 1)
	{//ï¿½Å¸ï¿½ ï¿½ï¿½ï¿½ï¿½Ø¾ï¿½ï¿½Ï´Âµï¿½... ï¿½Ù¸ï¿½ Ä­ï¿½ï¿½ ï¿½Ö³ï¿½...

		float	fLongest;
		int		iCount;

		for (int i = 0; i < vecDistance.size(); ++i)
		{
			if (i == 0)
			{
				fLongest = vecDistance[i];
			}
			else
			{
				if (fLongest > vecDistance[i])
				{
					fLongest = vecDistance[i];
					iCount = i;
				}
			}
		}

		if (_fpOutDistance != nullptr)
		{	
			*_fpOutDistance = fLongest;
		}
		if (_vpOutIntersection != nullptr)
		{
			*_vpOutIntersection = vecIntersection[iCount];
		}

		*_PickingOjbect = vecPickObj[iCount];
		
		return true;
	}

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

	/*ºä ½ºÆäÀÌ½º ±îÁö¸¸ º¯È¯.*/
	m_vRayOrigin = { 0.f,0.f,0.f }; //ºä½ºÆäÀÌ½º ÀÚÃ¼°¡ Ä«¸Þ¶ó ±âÁØÀ¸·Î ¿É¢hµéÀ» ¹èÄ¡ÇÏ´Â°Å¶ó¼­
	//½ÃÀÛÁöÁ¡Àº 0,0,0ÀÓ
	EngineFunction->Get_MainCamera()->Screen2World(_ScreenPos,0, &m_vRayDir);
	//°Å¸® 0ÀÌ¶ó¼­ °á±¹ °Á Ä«¸Þ¶ó À§Ä¡/RayOriginÀÌ¶û °°À½.

	/* ¿ùµå½ºÆäÀÌ½º º¯È¯ */
	Matrix invViewSpace;
	EngineFunction->Get_Dx9_Device()->GetTransform(D3DTS_VIEW, &invViewSpace);
	D3DXMatrixInverse(&invViewSpace, 0, &invViewSpace);
	//½ÃÀÛ ÁöÁ¡Àº À§Ä¡ º¤ÅÍ(w = 1)
	//=>TransformCoord
	D3DXVec3TransformCoord(&m_vRayOrigin, &m_vRayOrigin, &invViewSpace);

	//¹æÇâÀº ¹æÇâº¤ÅÍ(w = 0)
	//=>TransformNormal
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &invViewSpace);
	//³ë¸»¶óÀÌÁî±îÁö.
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);	
	//
	////m_vRayDir = m_vRayOrigin + Temp;
#pragma endregion

	////¾îÂ÷ÇÇ ºä 0,0,0 ¿¡¼­ ¿ùµå·Î ³Ñ¾î¿À¸é Ä«¸Þ¶ó À§Ä¡ÀÓ.
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
//{ //¹«ÇÑÇÑ Á÷¼±°ú Á¡»çÀÌÀÇ °Å¸®
//	Vector3 AB = L1.end - L1.start;
//	Vector3 AP = P1 - L1.start;
//
//	float area = Nalmak_Math::Magnitude(Nalmak_Math::Cross(AB, AP));
//	float CD = area / Nalmak_Math::Magnitude(AB);
//
//	return CD;
//}
//¸Å±×´ÏÆ©µå : sqrtf(_value.x * _value.x + _value.y * _value.y + _value.z * _value.z);

//Vector3 center = render->GetTransform()->GetWorldPosition();
//{
//¼±ºÐ°ú Á÷¼± »çÀÌÀÇ °Å¸®.
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
