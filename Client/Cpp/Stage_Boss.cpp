#include "stdafx.h"
#include "..\Header\Stage_Boss.h"
#include "StageManager.h"


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
	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_BOSS);


}

void Stage_Boss::UpdateState()
{
}

void Stage_Boss::ExitState()
{
}
