#pragma once

#ifndef _MENU_SELECTOR_H_
#define _MENU_SELECTOR_H_

#include "Component.h"

class UI;
class MenuSelector :	public Component
{
public:
	struct Desc
	{
		UI*		StartButton = nullptr;
		UI*		ExitButton = nullptr;

	};

public:
	MenuSelector(Desc* _desc);
	virtual ~MenuSelector();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;
	
public: /* func */

public: /* Get */

public: /* Set */

private:
	UI*			m_vecButtons[2];


};

#endif //_MENU_SELECTOR_H_