#include "stdafx.h"
#include "..\Header\Player_Reload.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
#include "AnimationController.h"
#include "..\..\Engine\Header\StateController.h"
#include "Player_TestAttack.h"
#include "Player_Attack.h"


Player_Reload::Player_Reload()
{
}


Player_Reload::~Player_Reload()
{
}

void Player_Reload::Initialize()
{
}

void Player_Reload::EnterState()
{
}

void Player_Reload::UpdateState()
{

	
	int temp = m_GameObject->Get_Component<AnimationController>()->Get_CurAnimIndex();
	
	if (temp != 2)
	{
		m_GameObject->Get_Component<AnimationController>()->Play(2);
	}


	//switch (m_GameObject->Get_Component<Player_Attack>()->Get_CurWeaponIndex())
	//{
	//case 0:
	//{
	//

	//	if (temp != 6)
	//	{
	//		m_GameObject->Get_Component<AnimationController>()->Play(6); 
	//	}
	//}
	//break;

	//case 1:
	//{
	//	if (temp != 0)
	//	{
	//		m_GameObject->Get_Component<AnimationController>()->Play(0);
	//	}
	//}
	//break;

	//default:
	//	break;
	//}

	if (m_GameObject->Get_Component<AnimationController>()->IsEnd())
	{
		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
	}
}

void Player_Reload::ExitState()
{

}
