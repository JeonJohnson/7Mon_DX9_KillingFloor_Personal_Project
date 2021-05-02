#pragma once

#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

//class StaticMesh;
//class AnimMesh;
class Mesh;
class Shader;

class DLL_STATE Mesh_Renderer : public Renderer
{
public:
	struct Desc
	{
		wstring szMeshName = L"";
		//int		iAnimIndex = 1;
		//wstring szTexturePath = L"";

		//Vector3		vPos = { 0.f,0.f,0.f };
		//Vector3		vRot = { 0.f, 0.f, 0.f };
		//Vector3		vScale = { 1.f,1.f,1.f };

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
	void		Create_Shader();
	void		Setup_ShaderTable();


public: /* Get */
	Mesh*		Get_Mesh();

public: /* Set */
	void		Set_Mesh(Mesh* _pMesh);
	void		Set_Mesh(const wstring& _pMeshName);


private:
	Mesh*			m_pMesh = nullptr;
	Shader*			m_pShaderCom = nullptr;
	LPD3DXEFFECT	m_pEffectCom = nullptr;
	//Vector3			m_vPosition;
	//Vector3			m_vRoation;
	//Vector3			m_vScale;
	//Matrix			m_matWorld;
};

#endif//_MESH_RENDERER_H_