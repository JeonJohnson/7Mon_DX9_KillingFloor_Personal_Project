#include "..\Header\SphereCollider.h"
#include "Mesh_Renderer.h"
#include "GameObject.h"
#include "VIBuffer_Renderer.h"
#include "Engine_Mother.h"

SphereCollider::SphereCollider(Desc * _desc)
{
	m_fRadius = _desc->fRadius;
	m_vOffset = _desc->vOffset;
	m_iCollisionLayer = _desc->iCollisionLayer;
	m_szColName = _desc->szColName;

	

	m_pDebuging = INSTANTIATE(0,L"SphereCollider");
	m_pDebuging->Set_Scale(Vector3(m_fRadius*2, m_fRadius*2, m_fRadius*2));

	//Áö±Ý ÃÑ½î¸é¼­ ‘‘ ²÷Å°´Â ÀÌÀ¯ ¾êÀÓ. °³ ¤Ñ ½Ã¹ß
	//´Ù¸¥ ¹öÆÛ·Î ±×·Áµµ ¶È°°À½ ¾Æ ¹ÌÄ¡°Ú³× ½ËÆÈ

#ifdef _DEBUG
	VIBuffer_Renderer::Desc colDesc;
	colDesc.wBufferName = L"Sphere_Debug";
	m_pDebuging->Add_Component<VIBuffer_Renderer>(&colDesc);
#endif //_DEBUG

}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Initialize()
{
}

void SphereCollider::Update()
{
	//¾ê´Â ¹®Á¦ ¾Æ´Ô.
	//¾ê ¾È ³Ö¾îµµ »ý¼º¸¸ ÇÏ´Â ÀÚÃ¼°¡ ²÷Å´ .
	//ÇØ°á.
	Vector3 MotherPos = m_Transform->Get_Position();
	m_pDebuging->Set_Position(MotherPos + m_vOffset);
	m_vCenter = m_pDebuging->Get_Position();

	

}

void SphereCollider::LateUpdate()
{
}

void SphereCollider::ReadyRender()
{
}

void SphereCollider::Release()
{
	m_pDebuging->Set_Alive(false);
}

bool SphereCollider::Sphere2Sphere(SphereCollider * _pStart, SphereCollider * _pDest)
{
	Vector3 vPosStart = _pStart->Get_Center();
	Vector3 vPosDest = _pDest->Get_Center();

	Vector3 vDist = vPosDest - vPosStart;
	float vDistLength = D3DXVec3Length(&vDist);

	//Engine_Mother::Get_Instance()->DebugLog(L"Collider Test : " +to_wstring(vDistLength));

	if (vDistLength <= _pStart->Get_Radius() + _pDest->Get_Radius())
	{
		return true;
	}
	
	return false;

}

bool SphereCollider::Collision_Check(GameObject * _pGameObejct, const wstring & _szColName)
{
	if (m_bCheck)
	{
		SphereCollider* TempSphereCol = _pGameObejct->Get_Component<SphereCollider>();

		if (TempSphereCol == nullptr)
		{
			return false;
		}

		if (Sphere2Sphere(this, TempSphereCol))
		{
			return true;
		}

		return false;
	}
	return false;

}

bool SphereCollider::Collision_Check(_object_Tag _iTag,
	const wstring & _szObjName, const wstring & _szColName)
{
	return false;
}

Vector3 SphereCollider::Get_Center()
{
	return m_vCenter;
}

float SphereCollider::Get_Radius()
{
	return m_fRadius;
}

bool SphereCollider::Get_Check()
{
	return m_bCheck;
}

void SphereCollider::Set_Check(bool _bCheack)
{
	m_bCheck = _bCheack;
}

