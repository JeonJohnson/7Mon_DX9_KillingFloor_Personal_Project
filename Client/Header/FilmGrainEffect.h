#pragma once

#ifndef _FILMGRAINEFFECT_H_
#define _FILMGRAINEFFECT_H_

#include "Component.h"

class UI;
class FilmGrainEffect :	public Component
{
public:
	struct Desc
	{
		UI* pFilmGrain = nullptr;

	};
public:
	FilmGrainEffect(Desc* _desc);
	virtual ~FilmGrainEffect();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;
	
public:

public:

public:

private:
	UI*			m_pFilmGrain = nullptr;
};

#endif //_FILMGRAINEFFECT_H_