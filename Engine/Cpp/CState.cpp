#include "..\Header\CState.h"

#include "StateController.h"


CState::CState()
{
}


CState::~CState()
{
}

void CState::LateUpdateState()
{
}

void CState::ReadyRenderState()
{
}

void CState::Set_State(const wstring & _szNextState)
{
	m_pStateController->Set_State(_szNextState);
}
