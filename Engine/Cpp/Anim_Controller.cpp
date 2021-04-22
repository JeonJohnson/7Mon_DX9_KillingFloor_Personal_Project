#include "..\Header\Anim_Controller.h"

#include "GameObject.h"
#include "Mesh_Renderer.h"
#include "Mesh.h"

Anim_Controller::Anim_Controller(Desc * _desc)
{
}

Anim_Controller::~Anim_Controller()
{
}

void Anim_Controller::Initialize()
{
	if (m_GameObject != nullptr)
	{
		Mesh_Renderer* Temp_MeshRenderer = m_GameObject->Get_NewComponent<Mesh_Renderer>();
		
		if (Temp_MeshRenderer != nullptr)
		{
			Temp_MeshRenderer->Get_Mesh()->Get_AnimationController();
		}
	}
}

void Anim_Controller::Update()
{
}

void Anim_Controller::LateUpdate()
{
}

void Anim_Controller::ReadyRender()
{
}

void Anim_Controller::Release()
{
}
