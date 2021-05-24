#include "stdafx.h"
#include "..\Header\BombExplosion.h"
#include "SphereCollider.h"
#include "Zed.h"

BombExplosion::BombExplosion(Desc * _desc)
{
	m_iDmg = _desc->iDmg;
	m_fMaxTime = _desc->fLiveTime;
}

BombExplosion::~BombExplosion()
{
}

void BombExplosion::Initialize()
{
}

void BombExplosion::Update()
{
	if (m_pCol == nullptr)
	{
		m_pCol = m_GameObject->Get_Component<SphereCollider>();
	}

	m_fTime += fTime;

	if (m_fTime >= 0.5f)
	{
		m_GameObject->Set_Alive(false);
	}

	auto pZeds = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_ZED);

	for (auto& zed : pZeds)
	{
		if (m_pCol->Collision_Check(zed, L"Body"))
		{
			if (auto pStatus = zed->Get_Component<Zed>())
			{
				pStatus->Damaged(m_iDmg);
			}
			//m_pCol->Set_Check(false);

			//m_GameObject->Set_Alive(false);
			return;
		}
	}

}

void BombExplosion::LateUpdate()
{
}

void BombExplosion::ReadyRender()
{
}

void BombExplosion::Release()
{
}
