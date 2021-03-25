#pragma once

#ifndef _VIBUFFER_RENDERER_H_
#define _VIBUFFER_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

class _declspec(dllexport) VIBuffer_Renderer :
	public Renderer
{
	//VIBuffer Objģ������ Component�� �����ؼ�
	//Desc�� �ް� �����ؼ� �˸��� VIBuffer�� �������� ������
	//RenderManager�� �Ѱ��� ģ��.
	//Renderer�� Component�� ��ӹް� ������ �ֵ� �� į������Ʈ��
public:
	struct Desc 
	{


	};

public:
	VIBuffer_Renderer(Desc* _desc);
	virtual ~VIBuffer_Renderer();

public:
	// Renderer��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

	
};

#endif