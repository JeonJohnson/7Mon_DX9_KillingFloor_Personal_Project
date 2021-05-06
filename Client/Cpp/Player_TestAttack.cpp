#include "stdafx.h"
#include "..\Header\Player_TestAttack.h"

#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"
//#include "Anim_Controller.h"
#include "AnimationController.h"
#include "Component.h"
#include "..\..\Engine\Header\StateController.h"
#include "StateController.h"

Player_TestAttack::Player_TestAttack(Desc * _desc)
{

	m_pWeapon_Mesh = _desc->pMeshRenderer;

	//m_arrWeapons[0] = _desc->pPrimary;
	//m_arrWeapons[1] = _desc->pSecondary;
	//m_arrWeapons[2] = _desc->pMelee;

	m_arrWeapons[0] = _desc->szPrimary;
	m_arrWeapons[1] = _desc->szSecondary;
	m_arrWeapons[2] = _desc->szMelee;

	m_pWeaponAnim = _desc->pAnimCtrl;

	//m_pWeaponAnim->Set_AnimIndex(0);

	m_iCurWeaponIndex = 0;
};



Player_TestAttack::~Player_TestAttack()
{
}

void Player_TestAttack::Initialize()
{
}

void Player_TestAttack::Update()
{
	Swap();
	Reload();
	Shoot();

	wstring temp = L"Cur Frame : " + to_wstring(m_pWeaponAnim->Get_CurFrame());
	wstring temp2 = L"Max Frame : " + to_wstring(m_pWeaponAnim->Get_MaxFrame());
	wstring temp3 = L"Cur State : " + m_GameObject->Get_Component<StateController>()->Get_CurStateName();
	DEBUG_LOG(temp);
	DEBUG_LOG(temp2);
	DEBUG_LOG(temp3);

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

void Player_TestAttack::LateUpdate()
{
}

void Player_TestAttack::ReadyRender()
{
}

void Player_TestAttack::Release()
{
}

bool Player_TestAttack::IronSight()
{
	return false;
}

bool Player_TestAttack::Shoot()
{
	if (MouseDown(KEY_STATE_LMouse))
	{
		//m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Att");


		//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(4);
		switch (m_iCurWeaponIndex)
		{
		case 0:
		{
		
			//m_pWeaponAnim->Set_AnimIndex_NoBlend(4);
			m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Att");
			//m_pWeaponAnim->Play(4);
			
		}
		break;

		case 1:
		{
			m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Att");
			//m_pWeaponAnim->Play(3);
		}
		break;

		case 2:
		{
			m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Att");
			//m_pWeaponAnim->Play(7);
		}
		break;

		default:
			break;
		}
		
		return true;
	}
	//if (MouseUp(KEY_STATE_LMouse))
	//{
	//	//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(5);
	//	
	//	return true;
	//}

	return false;
}

bool Player_TestAttack::Reload()
{
	wstring temp = m_GameObject->Get_Component<StateController>()->Get_CurStateName();
	
	
	
	if (m_GameObject->Get_Component<StateController>()->Get_CurStateName() != L"Player_Reload")
	{
		if (KeyDown(KEY_STATE_R))
		{
			//m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Reload");

			switch (m_iCurWeaponIndex)
			{
			case 0:
			{
				m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Reload");
				//m_pWeaponAnim->Play(6);
			}
			break;

			case 1:
			{
				m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Reload");
				//m_pWeaponAnim->Play(0);
			}
			break;


			default:
				break;
			}
			return true;
		}
	}
		return false;

}

bool Player_TestAttack::Swap()
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
		//m_pWeaponAnim->Setup_AnimController(m_GameObject);
		m_pWeaponAnim->SetUp_AnimCtrl();

		switch (m_iNewWeaponIndex)
		{
		case 0:
		{
			//m_pWeaponAnim->Set_CurFrame(0.f);
			m_pWeaponAnim->Play(0);
		
			//m_pWeaponAnim->Set_AnimReset(0);
		}
		break;

		case 1:
		{
			//m_pWeaponAnim->Set_CurFrame(0.f);
			m_pWeaponAnim->Play(2);
			//m_pWeaponAnim->Set_AnimReset(2);
		}
		break;

		case 2:
		{
			//m_pWeaponAnim->Set_CurFrame(0.f);
			m_pWeaponAnim->Play(0);
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

int Player_TestAttack::Get_CurWeaponIndex()
{
	return m_iCurWeaponIndex;
}
