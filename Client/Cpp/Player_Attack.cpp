#include "stdafx.h"
#include "..\Header\Player_Attack.h"

#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"
#include "Anim_Controller.h"
#include "Component.h"
#include "..\..\Engine\Header\StateController.h"

Player_Attack::Player_Attack(Desc * _desc)
{

	m_pWeapon_Mesh = _desc->pMeshRenderer;

	//m_arrWeapons[0] = _desc->pPrimary;
	//m_arrWeapons[1] = _desc->pSecondary;
	//m_arrWeapons[2] = _desc->pMelee;

	m_arrWeapons[0] = _desc->szPrimary;
	m_arrWeapons[1] = _desc->szSecondary;
	m_arrWeapons[2] = _desc->szMelee;

	m_pWeaponAnim = _desc->pAnimCtrl;

};



Player_Attack::~Player_Attack()
{
}

void Player_Attack::Initialize()
{
}

void Player_Attack::Update()
{
	Swap();
	Reload();
	Shoot();

	//if (!Swap() && !Reload()) 
	//{
	//	//아무것도 안 눌렸을때 => 둘 다 false
	//	if (m_iCurWeaponIndex == 1)
	//	{
	//		if (m_pWeaponAnim->Get_CurIndex() != 4)
	//		{
	//			m_pWeaponAnim->Set_AnimIndex(4);
	//		}
	//	}
	//	else 
	//	{
	//		if (m_pWeaponAnim->Get_CurIndex() != 2)
	//		{		m_pWeaponAnim->Set_AnimIndex(2);		}
	//	}
	//}
}

void Player_Attack::LateUpdate()
{
}

void Player_Attack::ReadyRender()
{
}

void Player_Attack::Release()
{
}

bool Player_Attack::IronSight()
{
	return false;
}

bool Player_Attack::Shoot()
{
	if (MouseDown(KEY_STATE_LMouse))
	{
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Att");


		////Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(4);
		//switch (m_iCurWeaponIndex)
		//{
		//case 0:
		//{
		//	m_pWeaponAnim->Set_AnimIndex(4);
		//}
		//break;

		//case 1:
		//{
		//	m_pWeaponAnim->Set_AnimIndex(3);
		//}
		//break;

		//case 2:
		//{
		//	m_pWeaponAnim->Set_AnimIndex(7);
		//}
		//break;

		//default:
		//	break;
		//}
		//
		//return true;
	}
	//if (MouseUp(KEY_STATE_LMouse))
	//{
	//	//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(5);
	//	
	//	return true;
	//}

	return false;
}

bool Player_Attack::Reload()
{
	if (KeyPress(KEY_STATE_R))
	{
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Reload");
		//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(1);
	/*	switch (m_iCurWeaponIndex)
		{
		case 0:
		{
			m_pWeaponAnim->Set_AnimIndex(6);
		}
		break;

		case 1:
		{
			m_pWeaponAnim->Set_AnimIndex(0);
		}
		break;


		default:
			break;
		}
		return true;*/
	}

	return false;
}

bool Player_Attack::Swap()
{
	if (KeyDown(KEY_STATE_1))
	{
		m_iNewWeaponIndex = 0;
	}
	if (KeyDown(KEY_STATE_2))
	{
		m_iNewWeaponIndex = 1;
	}
	if (KeyDown(KEY_STATE_3))
	{
		m_iNewWeaponIndex = 2;
	}

	if (m_iCurWeaponIndex != m_iNewWeaponIndex)
	{
		m_pWeapon_Mesh->Set_Mesh(m_arrWeapons[m_iNewWeaponIndex]);
		m_pWeaponAnim->Setup_AnimController(m_GameObject);
		

		switch (m_iNewWeaponIndex)
		{
		case 0:
		{
			//m_pWeaponAnim->Set_CurFrame(0.f);
			m_pWeaponAnim->Set_AnimIndex(0);
		
			//m_pWeaponAnim->Set_AnimReset(0);
		}
		break;

		case 1:
		{
			//m_pWeaponAnim->Set_CurFrame(0.f);
			m_pWeaponAnim->Set_AnimIndex(2);
			//m_pWeaponAnim->Set_AnimReset(2);
		}
		break;

		case 2:
		{
			//m_pWeaponAnim->Set_CurFrame(0.f);
			m_pWeaponAnim->Set_AnimIndex(0);
			//m_pWeaponAnim->Set_AnimReset(0);
		}
		break;

		default:
			break;
		}
		
		m_iCurWeaponIndex = m_iNewWeaponIndex;

		return true;
	}

	return false;
}

int Player_Attack::Get_CurWeaponIndex()
{
	return m_iCurWeaponIndex;
}
