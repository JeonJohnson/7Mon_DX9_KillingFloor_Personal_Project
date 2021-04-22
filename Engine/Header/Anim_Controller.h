#pragma once

#ifndef _ANIM_CONTROLLER_H_
#define _ANIM_CONTROLLER_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE Anim_Controller :	public Component
{
public:
	struct Desc
	{
		


	};

public:
	explicit Anim_Controller(Desc* _desc);
	virtual ~Anim_Controller();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public: /* Get */

public: /* Set */

private:
	LPD3DXANIMATIONCONTROLLER		m_pDX9_AnimController = nullptr;


};


#endif //_ANIM_CONTROLLER_H_