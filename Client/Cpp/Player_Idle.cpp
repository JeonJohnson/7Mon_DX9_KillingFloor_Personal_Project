#include "stdafx.h"
//#include "..\Header\Player_Idle.h"
//#include "..\..\Engine\Header\Anim_Controller.h"
//#include "Player_Attack.h"
//
//
//Player_Idle::Player_Idle()
//{
//}
//
//
//Player_Idle::~Player_Idle()
//{
//}
//
//void Player_Idle::Initialize()
//{
//	m_pAnimCtrl = m_GameObject->Get_NewComponent<Anim_Controller>();
//	assert(L"AnimCtrl find failed" && m_pAnimCtrl);
//
//	m_pWeapon = m_GameObject->Get_NewComponent<Player_Attack>();
//
//}
//
//void Player_Idle::EnterState()
//{
//}
//
//void Player_Idle::UpdateState()
//{
//	
//	switch (m_pWeapon->Get_CurWeaponIndex())
//	{
//	case 0:
//	{m_pAnimCtrl->Set_AnimIndex(2); }
//	break;
//
//	case 1:
//	{m_pAnimCtrl->Set_AnimIndex(4); }
//	break;
//
//	case 2:
//	{m_pAnimCtrl->Set_AnimIndex(2); }
//	break;
//
//	default:
//		break;
//	}
//}
//
//void Player_Idle::ExitState()
//{
//}
