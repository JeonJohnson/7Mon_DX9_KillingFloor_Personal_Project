#pragma once
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

