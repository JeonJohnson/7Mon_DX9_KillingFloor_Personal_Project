#pragma once

#ifndef _VIBUFFER_RENDERER_H_
#define _VIBUFFER_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

class _declspec(dllexport) VIBuffer_Renderer :
	public Renderer
{
	//VIBuffer Obj친구들을 Component로 생성해서
	//Desc로 받고 구분해서 알맞은 VIBuffer의 정보값을 가져와
	//RenderManager로 넘겨줄 친구.
	//Renderer가 Component를 상속받고 있으니 애도 걍 캄ㅡ포난트임
public:
	struct Desc 
	{


	};

public:
	VIBuffer_Renderer(Desc* _desc);
	virtual ~VIBuffer_Renderer();

public:
	// Renderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

	
};

#endif