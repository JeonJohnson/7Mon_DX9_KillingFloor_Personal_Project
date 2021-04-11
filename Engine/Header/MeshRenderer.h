#pragma once

#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

class StaticMesh;
class DLL_STATE MeshRenderer : public Renderer
{
public:
	struct Desc
	{


	};
public:
	MeshRenderer(Desc* _desc);
	virtual ~MeshRenderer();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:

public:

public:

private:
	StaticMesh*		m_pStaticMesh = nullptr;
};

#endif//_MESH_RENDERER_H_