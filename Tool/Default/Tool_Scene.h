#pragma once
#include "Scene.h"
class Tool_Scene :
	public Scene
{
public:
	Tool_Scene();
	virtual ~Tool_Scene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

