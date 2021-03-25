#pragma once

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Engine_Include.h"
#include "Component.h"

class _declspec(dllexport) Renderer : public Component
{
	//Renderer�� ������ ģ���� �ᱹ Component��
	//Component�� Cycle �� ��
	//LateUpdate���� RenderManager�� RenderingList�� ����.
	//�׷��� �ڿ������� ������ �ϰ���.
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