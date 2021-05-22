#pragma once

#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

#include "Component.h"

#include "Include.h"

class StateController;

class StageManager : public Component
{
public:
	struct Desc
	{
		
	};
public:
	StageManager(Desc* _desc);
	virtual ~StageManager();

private:
	static StageManager* m_pInstance;
public:
	static StageManager* Get_Instance();
	static void			 Destory_Instance();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public: /* Get */
	STAGE_NAME		Get_CurStageName();


public: /* Set */
	void			Set_CurStage(STAGE_NAME _eCurStageName);

private:
	StateController*		m_pStateCtrl = nullptr;
	
	STAGE_NAME				m_eCurStage;
	bool					m_bClearStage[3] = { false };


};

#endif //_STAGE_MANAGER_H_