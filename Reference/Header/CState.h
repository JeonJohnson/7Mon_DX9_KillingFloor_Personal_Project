#pragma once

#ifndef _CSTATE_H_
#define _CSTATE_H_

#include "Engine_Include.h"

class GameObject;
class Transform;

class DLL_STATE CState
{
	friend class StateController;

public:
	CState();
	virtual ~CState();

private:
	virtual void Initialize() = 0;
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void LateUpdateState();
	virtual void ReadyRenderState();
	virtual void ExitState() = 0;

public: /* Function */

public: /* Get */


	//for black board
public: /* Set */
	void Set_State(const wstring& _szNextState);

	//for black board
protected:
	GameObject*			m_GameObject = nullptr;
	Transform*			m_Transform = nullptr;
	StateController*	m_pStateController = nullptr;

};

#endif //_STATE_H_