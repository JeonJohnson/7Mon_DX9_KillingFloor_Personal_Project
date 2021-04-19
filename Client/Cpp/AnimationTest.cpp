#include "stdafx.h"
#include "..\Header\AnimationTest.h"
#include "../../Reference/Header/Mesh_Renderer.h"
#include "../../Reference/Header/GameObject.h"
#include "AnimMesh.h"
#include "AnimationController.h"

AnimationTest::AnimationTest(Desc * _desc)
{
}

AnimationTest::~AnimationTest()
{
}

void AnimationTest::Initialize()
{
}

void AnimationTest::Update()
{
	if (MousePress(KEY_STATE_LMouse))
	{
		Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_AnimMesh()->Get_AnimationController()->Set_AnimationSet(1);
	}
	else { Get_GameObject()->Get_Component<Mesh_Renderer>()->Get_AnimMesh()->Get_AnimationController()->Set_AnimationSet(2); }
}

void AnimationTest::LateUpdate()
{
}

void AnimationTest::ReadyRender()
{
}

void AnimationTest::Release()
{
}
