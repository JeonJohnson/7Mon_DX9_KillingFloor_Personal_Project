#include "..\Header\StateController.h"

#include "CState.h"


StateController::StateController(Desc * _desc)
{
}

StateController::~StateController()
{

}

void StateController::Initialize()
{
	assert("Plz Set InitState" && m_pCurState);

	for (auto state : m_mapStateList)
	{
		state.second->Initialize();
	}

	m_pCurState->EnterState();
}

void StateController::Update()
{
	m_pCurState->UpdateState();
}

void StateController::LateUpdate()
{
	m_pCurState->LateUpdateState();
}

void StateController::ReadyRender()
{
	m_pCurState->ReadyRenderState();
}

void StateController::Release()
{
	for (auto& state : m_mapStateList)
	{
		Safe_Delete(state.second);
	}
	m_mapStateList.clear();
}

bool StateController::Compare_State(const wstring & _StateName)
{
	assert("Current state is nullptr" && m_pCurState);

	if (m_mapStateList.find(_StateName) == m_mapStateList.end())
	{
		assert(0 && L"그런 이름 스테이트 없읍니다.");
	}

	if (m_mapStateList[_StateName] == m_pCurState)
	{	return true;	}
	else
	{
		return false;
	}
	
}

 wstring  StateController::Get_CurStateName()
{
	for (auto& state : m_mapStateList)
	{
		if (state.second == m_pCurState)
		{
			return state.first;
		}
	}

	return L"";
}

void StateController::Set_InitState(const wstring & _InitStateName)
{
	auto iter_find = m_mapStateList.find(_InitStateName);

	if (iter_find == m_mapStateList.end())
	{
		assert(0 && L"There's no State that have name");
	}
	else 
	{
		m_pCurState = m_mapStateList[_InitStateName];
	}
}

void StateController::Set_State(const wstring & _NextStateName)
{
	if (m_mapStateList.find(_NextStateName) == m_mapStateList.end())
	{
		assert(0 && L"There's no State that have name");
	}


	m_pCurState->ExitState();
	m_pPreState = m_pCurState;
	m_pCurState = m_mapStateList[_NextStateName];
	assert(L"NextState is null" && m_pCurState);
	m_pCurState->EnterState();

}
