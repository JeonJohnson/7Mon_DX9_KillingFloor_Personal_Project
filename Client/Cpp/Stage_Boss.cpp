#include "stdafx.h"
#include "..\Header\Stage_Boss.h"
#include "StageManager.h"
#include "HudManager.h"


Stage_Boss::Stage_Boss()
{
}


Stage_Boss::~Stage_Boss()
{
}

void Stage_Boss::Initialize()
{
}

void Stage_Boss::EnterState()
{

	HudManager::Get_Instance()->Get_Hud(L"EnemyCount")->Set_Active(true);
	HudManager::Get_Instance()->Get_Hud(L"Clock")->Set_Active(false);

	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_BOSS);


}

void Stage_Boss::UpdateState()
{
}

void Stage_Boss::ExitState()
{
}
