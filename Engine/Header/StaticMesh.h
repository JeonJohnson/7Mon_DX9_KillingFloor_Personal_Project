#pragma once

#ifndef _STATIC_MESH_H_
#define _STATIC_MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class Texture;
class DLL_STATE StaticMesh : public CResource
{
public:
	StaticMesh();
	virtual ~StaticMesh();

public:
	virtual void Initialize() override;
	virtual void Release() override;


public:
	HRESULT Insert_StaticMesh(const wstring& _szMeshFullPath, const wstring& _szTexFullPath);
	HRESULT Render_Texture(int _iNum);

public: /* Get */
	Texture*		Get_Texture();
	const DWORD&	Get_MaterialCount() const;
	LPD3DXMESH		Get_Mesh();

public: /* Set */
	void			Set_Texture(Texture* _texture);

private:
	//LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	//LPD3DXBUFFER -> 그냥 빈 메모리 공간임.
		//매쉬 로드할때 어떤 형태로 얼마나 필요한지 모르니까
	LPD3DXBUFFER			m_pAdjacency = nullptr;
	LPD3DXBUFFER			m_pMaterials = nullptr;
	DWORD					m_ulMaterial_Count = 0;
	LPD3DXMESH				m_pMesh = nullptr;
	                                       
	Texture*				m_pTexture = nullptr;

};


#endif//_STATIC_MESH_H_