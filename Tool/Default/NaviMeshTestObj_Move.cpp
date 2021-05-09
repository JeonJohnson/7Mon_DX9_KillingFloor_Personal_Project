#include "stdafx.h"
#include "NaviMeshTestObj_Move.h"

#include "NaviMesh.h"


NaviMeshTestObj_Move::NaviMeshTestObj_Move(Desc * _desc)
{
}

NaviMeshTestObj_Move::~NaviMeshTestObj_Move()
{
}

void NaviMeshTestObj_Move::Initialize()
{
}

void NaviMeshTestObj_Move::Update()
{
	Move();
}

void NaviMeshTestObj_Move::LateUpdate()
{
}

void NaviMeshTestObj_Move::ReadyRender()
{
}

void NaviMeshTestObj_Move::Release()
{
}

void NaviMeshTestObj_Move::Move()
{
	
		Vector3 vPos = m_Transform->Get_Position();
		Vector3 vForward = m_Transform->Get_Forward();
		D3DXVec3Normalize(&vForward, &vForward);

		if (KeyPress(KEY_STATE_Up))
		{
			if (m_pNaviMesh != nullptr)
			{
				m_Transform->Set_Position(m_pNaviMesh->MoveOn(vPos, (vForward * dTime * 50.f)));
			}
			else 
			{
				m_Transform->Add_Position(vForward * dTime * 50.f);
			}

		}
		//else if (KeyPress(KEY_STATE_Down))
		//{

		//}

		if (KeyPress(KEY_STATE_Left))
		{
			m_Transform->RotateY(dTime * -60.f);
		}
		else if (KeyPress(KEY_STATE_Right))
		{
			m_Transform->RotateY(dTime * 60.f);
		}
	

}

void NaviMeshTestObj_Move::Set_NaviMesh(NaviMesh * _pNaviMesh)
{
	m_pNaviMesh = _pNaviMesh;
}
