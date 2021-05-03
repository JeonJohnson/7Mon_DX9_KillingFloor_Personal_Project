#pragma once

#ifndef _STATE_CONTROLLER_H_
#define _STATE_CONTROLLER_H_

#include "Engine_Include.h"

#include "Component.h"

class CState;

class DLL_STATE StateController : public Component
{
//얘를 게임 오브젝트에 컴포넌트로 넣어두고
//어디 포인터를 받아둔 뒤 거기다가 
//State를 상속받은 클래스를 Add_State를 해주면 됨.

public:
	struct Desc
	{

	
	};

public:
	explicit StateController(Desc* _desc);
	virtual ~StateController();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

#pragma region Template
public:
	template<class T>
	StateController*	Add_State(const wstring& _szStateName)
	{
		auto iter_find = m_mapStateList.find(_szStateName);

		if(iter_find != m_mapStateList.end())
		{
			assert("State name is already Exist" && 0);
		}
		else
		{
			CState* stateTemp = new T;

			//State는 그 해당 오브젝트의 ㄹㅇ 상태를 조절 할 녀석임으로
			//GameObect랑 Transform은 자주 씀.
			stateTemp->m_GameObject = m_GameObject;
			stateTemp->m_Transform = m_Transform;


			stateTemp->m_pStateController = this;
			m_mapStateList[_szStateName] = stateTemp;

			return this;
		}
		return nullptr;
	}

	template <class T>
	T* Get_State(const wstring& _stateName)
	{
		auto iter_find = m_mapStateList.find(_stateName);
		
		if (iter_find == m_mapStateList.end())
		{
			assert(0 && L"That State has not exist");
		}

		T*	StateTemp = (T*)(iter_find->second);
		return StateTemp;

	}

#pragma endregion

public : /* Func */
	bool Compare_State(const wstring& _StateName);

public: /* Get */
	 wstring Get_CurStateName();
	

public: /* Set */
	void Set_InitState(const wstring& _InitStateName);
	void Set_State(const wstring& _NextStateName);

	//black board


private:
	CState* m_pCurState = nullptr;
	CState* m_pPreState = nullptr;
	map<wstring, CState*>	m_mapStateList;
	
	//Black Board

};

#endif //_STATE_CONTROLLER_H_