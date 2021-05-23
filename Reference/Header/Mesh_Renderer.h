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
		wstring szShaderName = L"Shader_Mesh";

		int		iRenderLayer = 1;
		
		//Matrix	matMeshMatrix;
		//int		iAnimIndex = 1;
		//wstring szTexturePath = L"";

		Vector3		vPos = { 0.f,0.f,0.f };
		Vector3		vRot = { 0.f, 0.f, 0.f };
		Vector3		vScale = { 1.f,1.f,1.f };

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
	void		Create_Shader(const wstring& _szShaderName);
	void		Setup_ShaderTable();
	void		Animating();

	void		Update_MeshTransform();
public: /* Get */
	Mesh*		Get_Mesh();

	Vector3		Get_MeshPos();
	Vector3		Get_MeshScale();
	Vector3		Get_MeshRot();

public: /* Set */
	void		Set_Mesh(Mesh* _pMesh);
	void		Set_Mesh(const wstring& _pMeshName);

	void		Set_MeshMatrix(const Matrix& _Mat);
	void		Set_MeshPos(const Vector3& _vPos);
	void		Set_MeshRot(const Vector3& _vRot);

	void		Add_MeshPos(const Vector3& _vPos);

	
	void		Add_MeshPosX(float _x);
	void		Add_MeshPosY(float _y);
	void		Add_MeshPosZ(float _z);
	
	void		Set_MeshPosX(float _x);
	void		Set_MeshPosY(float _y);
	void		Set_MeshPosZ(float _z);


private:
	Mesh*			m_pMesh = nullptr;
	Shader*			m_pShaderCom = nullptr;
	LPD3DXEFFECT	m_pEffectCom = nullptr;



	Vector3			m_vPosition;
	Vector3			m_vRotation;
	Vector3			m_vScale;
	Matrix			m_matMeshTransform;

};

#endif//_MESH_RENDERER_H_