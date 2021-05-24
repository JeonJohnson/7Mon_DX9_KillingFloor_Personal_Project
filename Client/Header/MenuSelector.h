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
		UI*		Loading = nullptr;
		UI*		Fade = nullptr;
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
	bool FadeIn();
	
	bool CutScene_Sound();
	
	bool FadeOUt();


public: /* Get */

public: /* Set */

private:
	UI*			m_vecButtons[2];

	UI*			m_pLoading = nullptr;

	UI*			m_pFade = nullptr;
	Sprite*		m_pFadeSprite = nullptr;

	bool		m_bCutScene = false;
	bool		m_bFadeIn = false;
	bool		m_bFadeOut = false;

	bool		m_bChopperFly = false;
	bool		m_bPullUp = false;
	bool		m_bRadio = false;
	bool		m_bExplosion = false;

	bool		m_bNextScene = false;
	float		m_fCutSceneTime = 0.f;
};

#endif //_MENU_SELECTOR_H_