#pragma once


#include "Component.h"

class Mesh_Renderer;
class Player_Attack : public Component
{
public:
	struct Desc
	{


	};
public:
	explicit Player_Attack(Desc* _desc);
	virtual ~Player_Attack();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void	IronSight();
	void	Shoot();
	void	Reload();
public:

public:

private:
	Mesh_Renderer*		Weapon_Mesh = nullptr;

};

