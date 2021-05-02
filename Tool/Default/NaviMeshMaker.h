#pragma once


#include "Tool_Include.h"

#include "Component.h"


class NaviMeshMaker :	public Component
{
public:
	struct Desc
	{


	};

public:
	explicit	NaviMeshMaker(Desc* _desc);
	virtual		~NaviMeshMaker();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:

private:
	Vector2		m_tMousePos;
	Vector3		m_vWorldPos;
};

