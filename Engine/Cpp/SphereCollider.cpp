#include "..\Header\SphereCollider.h"
#include "Mesh_Renderer.h"
#include "GameObject.h"

SphereCollider::SphereCollider(Desc * _desc)
{
	m_fRadius = _desc->fRadius;
	m_vOffset = _desc->vOffset;
	m_iCollisionLayer = _desc->iCollisionLayer;
	

	

	//m_pDebuging = INSTANTIATE()
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Initialize()
{
}

void SphereCollider::Update()
{
}

void SphereCollider::LateUpdate()
{
}

void SphereCollider::ReadyRender()
{
}

void SphereCollider::Release()
{
}
