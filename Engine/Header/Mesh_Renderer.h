#pragma once

#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

class StaticMesh;
class AnimMesh;
class DLL_STATE Mesh_Renderer : public Renderer
{
public:
	struct Desc
	{
		wstring szMeshName = L"";
		int		iAnimIndex = 30;
		//wstring szTexturePath = L"";

	};
public:
	Mesh_Renderer(Desc* _desc);
	virtual ~Mesh_Renderer();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	
public:

public: /* Get */
	AnimMesh*		Get_AnimMesh();

public: /* Set */

private:
	//StaticMesh*		m_pStaticMesh = nullptr;
	AnimMesh*		m_pAnimMesh = nullptr;
};

#endif//_MESH_RENDERER_H_