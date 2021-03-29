#pragma once

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Engine_Include.h"
#include "Component.h"

class DLL_STATE Renderer : public Component
{
	//Renderer�� ������ ģ���� �ᱹ Component��
	//Component�� Cycle �� ��
	//ReayRender���� RenderManager�� RenderingList�� ����.
	//�׷��� �ڿ������� ������ �ϰ���.


public:
	Renderer();
	virtual ~Renderer();

public:
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void ReadyRender() override;
	virtual void Render() override = 0;
	virtual void Release() override = 0;

public:
	LPDIRECT3DDEVICE9	m_pDX9Device = nullptr;

protected:
	int m_iRenderLayer = 0;
};

#endif //_RENDERER_H_