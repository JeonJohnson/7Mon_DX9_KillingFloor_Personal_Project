#pragma once

#ifndef _TOOL_SCEHE_H_
#define _TOOL_SCEHE_H_

#include "Scene.h"
class Tool_Scene :
	public Scene
{
public:
	Tool_Scene();
	virtual ~Tool_Scene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

#endif//_TOOL_SCEHE_H_