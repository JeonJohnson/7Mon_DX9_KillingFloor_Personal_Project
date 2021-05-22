#include "stdafx.h"
#include "..\Header\Stage_2.h"
#include "StageManager.h"
#include "HudManager.h"


Stage_2::Stage_2()
{
}


Stage_2::~Stage_2()
{
}

void Stage_2::Initialize()
{
}

void Stage_2::EnterState()
{
	HudManager::Get_Instance()->Get_Hud(L"EnemyCount")->Set_Active(true);
	HudManager::Get_Instance()->Get_Hud(L"Clock")->Set_Active(false);

	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_2);
}

void Stage_2::UpdateState()
{
	DEBUG_LOG(L"CurStage : Stage2_" + to_wstring(m_iCurPattern));

}

void Stage_2::ExitState()
{
}
