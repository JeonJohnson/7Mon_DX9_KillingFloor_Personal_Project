#pragma once

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Engine_Include.h"
#include "Component.h"

class _declspec(dllexport) Renderer : public Component
{
	//Renderer를 가지는 친구도 결국 Component라서
	//Component의 Cycle 돌 때
	//LateUpdate에서 RenderManager의 RenderingList로 보냄.
	//그러면 자연스럽게 렌더를 하것지.
	//

public:
	Renderer();
	virtual ~Renderer();

public:
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void ReadyRender() override = 0;
	virtual void Release() override = 0;

public:


};

#endif