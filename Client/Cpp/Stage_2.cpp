#include "stdafx.h"
#include "..\Header\Stage_2.h"
#include "StageManager.h"


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
	StageManager::Get_Instance()->Set_CurStage(STAGE_NAME::STAGE_2);
}

void Stage_2::UpdateState()
{
	DEBUG_LOG(L"CurStage : Stage2_" + to_wstring(m_iCurPattern));
}

void Stage_2::ExitState()
{
}
