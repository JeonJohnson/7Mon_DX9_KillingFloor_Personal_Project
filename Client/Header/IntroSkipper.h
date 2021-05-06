#pragma once

#ifndef _INTRO_SKIPPER_H_
#define _INTRO_SKIPPER_H_

#include "Component.h"
class IntroSkipper : public Component
{
public:
	struct Desc
	{
		class UI* pFade = nullptr;



	};
public:
	IntroSkipper(Desc* _desc);
	virtual ~IntroSkipper();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

public:

public:

public:

private:
	class UI*	m_pFade = nullptr;
	float		m_fFade;
	bool		m_bOn = true;
	
	bool		m_bOff = false;
	float		m_fDeltaTime = 0.f;
};

#endif //_INTRO_SKIPPER_H_