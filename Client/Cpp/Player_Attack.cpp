#include "stdafx.h"
#include "..\Header\Player_Attack.h"

#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"
#include "AnimationController.h"

Player_Attack::Player_Attack(Desc * _desc)
{

}

Player_Attack::~Player_Attack()
{
}

void Player_Attack::Initialize()
{
}

void Player_Attack::Update()
{
	
	Reload();
	Shoot();
}

void Player_Attack::LateUpdate()
{
}

void Player_Attack::ReadyRender()
{
}

void Player_Attack::Release()
{
}

void Player_Attack::IronSight()
{
}

void Player_Attack::Shoot()
{
	if (MousePress(KEY_STATE_LMouse))
	{
		//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(4);
	}
	if (MouseUp(KEY_STATE_LMouse))
	{
		//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(5);
	}

}

void Player_Attack::Reload()
{
	if (KeyPress(KEY_STATE_R))
	{
		//Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_Mesh()->Get_AnimationController()->Set_AnimationSet(1);
	}
}
