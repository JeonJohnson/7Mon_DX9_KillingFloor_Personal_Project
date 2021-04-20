#pragma once

#ifndef _HIERARCHY_LOADER_H_
#define _HIERARCHY_LOADER_H_

#include "Engine_Include.h"

class Hierarchy_Loader : public ID3DXAllocateHierarchy
{
	//AnimMesh���� 
	//D3DXLoadMeshHierachyFromX���� �ε��Ҷ� 
	//�ڵ����� �ݹ�Ǵ� �Լ��� ���ؼ� 
	//�߻� Ŭ������ ��ӹ޴� Ŭ����.

public:
	struct Desc
	{
		wstring szMiddlePath = L"";

	};

public:
	explicit	Hierarchy_Loader(Desc* _desc);
	virtual		~Hierarchy_Loader();
	
public:

public:
	// ID3DXAllocateHierarchy��(��) ���� ��ӵ�
	virtual HRESULT CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame) override;
	virtual HRESULT CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer) override;
	
	virtual HRESULT DestroyFrame(LPD3DXFRAME pFrameToFree) override;
	virtual HRESULT DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree) override;

public:

public:
	
public:
	
private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	wstring				m_szMiddleFolderPath;
};

#endif //_HIERACHY_LOADER_H_