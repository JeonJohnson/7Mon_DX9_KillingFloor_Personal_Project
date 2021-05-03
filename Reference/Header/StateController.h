#pragma once

#ifndef _STATE_CONTROLLER_H_
#define _STATE_CONTROLLER_H_

#include "Engine_Include.h"

#include "Component.h"

class CState;

class DLL_STATE StateController : public Component
{
//�긦 ���� ������Ʈ�� ������Ʈ�� �־�ΰ�
//��� �����͸� �޾Ƶ� �� �ű�ٰ� 
//State�� ��ӹ��� Ŭ������ Add_State�� ���ָ� ��.

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

			//State�� �� �ش� ������Ʈ�� ���� ���¸� ���� �� �༮������
			//GameObect�� Transform�� ���� ��.
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