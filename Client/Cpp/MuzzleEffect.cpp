#include "stdafx.h"
#include "..\Header\MuzzleEffect.h"

#include "Mesh.h"

MuzzleEffect::MuzzleEffect(Desc * _desc)
{
	m_fMaxScale = _desc->fmaxsize;
	m_fSpd = _desc->fSpd;

	m_pPlayer = _desc->pPlayer;
	m_pMesh = _desc->pMesh;
}

MuzzleEffect::~MuzzleEffect()
{
}

void MuzzleEffect::Initialize()
{

}

void MuzzleEffect::Update()
{
	PositionUpdate();
	ScaleUpdate();
	
}

void MuzzleEffect::LateUpdate()
{

}

void MuzzleEffect::ReadyRender()
{

}

void MuzzleEffect::Release()
{

}

void MuzzleEffect::PositionUpdate()
{
	Vector3	BarrelPos;
	Matrix temp = m_pMesh->Get_BoneLocalPosByName(L"tip");
	Matrix PlayerTransform = m_pPlayer->Get_Transform()->Get_WorldMatrix();
	Matrix ResultMatrix = temp * PlayerTransform;

	BarrelPos.x = ResultMatrix._41;
	BarrelPos.y = ResultMatrix._42;
	BarrelPos.z = ResultMatrix._43;

	m_Transform->Set_Position(BarrelPos);
	m_Transform->Set_Rotation(m_pPlayer->Get_Rotation());

}

void MuzzleEffect::ScaleUpdate()
{
	DEBUG_LOG(L"MuzzleEffect Size : " + to_wstring(m_Transform->Get_Scale().x));

	if (m_bOn)
	{
		m_Transform->Add_Scale(Vector3(m_fSpd * fTime
			, m_fSpd * fTime, m_fSpd * fTime));

		if (m_Transform->Get_Scale().x >= m_fMaxScale)
		{
			m_bOn = false;
		}
	}
	else
	{
		m_Transform->Add_Scale(Vector3(m_fSpd * -fTime, m_fSpd * -fTime, m_fSpd * -fTime));

		if (m_Transform->Get_Scale().x <= 0.f)
		{
			m_GameObject->Set_Alive(false);
		}
	}
}
