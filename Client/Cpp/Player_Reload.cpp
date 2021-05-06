#include "stdafx.h"
//#include "..\Header\Player_Reload.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
//#include "..\..\Engine\Header\StateController.h"
//#include "Player_Attack.h"
//
//
//Player_Reload::Player_Reload()
//{
//}
//
//
//Player_Reload::~Player_Reload()
//{
//}
//
//void Player_Reload::Initialize()
//{
//}
//
//void Player_Reload::EnterState()
//{
//}
//
//void Player_Reload::UpdateState()
//{
//	switch (m_GameObject->Get_Component<Player_Attack>()->Get_CurWeaponIndex())
//	{
//	case 0:
//	{
//		m_GameObject->Get_Component<Anim_Controller>()->Set_AnimIndex(6);
//	}
//	break;
//
//	case 1:
//	{
//		m_GameObject->Get_Component<Anim_Controller>()->Set_AnimIndex(0);
//	}
//	break;
//
//	default:
//		break;
//	}
//
//	if (m_GameObject->Get_Component<Anim_Controller>()->Get_End())
//	{
//		m_GameObject->Get_Component<StateController>()->Set_State(L"Player_Idle");
//	}
//}
//
//void Player_Reload::ExitState()
//{
//}
