#include "..\Header\Hierachy_Loader.h"



Hierachy_Loader::Hierachy_Loader()
{
}


Hierachy_Loader::~Hierachy_Loader()
{
}

HRESULT Hierachy_Loader::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	return E_NOTIMPL;
}

HRESULT Hierachy_Loader::CreateMeshContainer(LPCSTR Name, 
	CONST D3DXMESHDATA * pMeshData, 
	CONST D3DXMATERIAL * pMaterials, 
	CONST D3DXEFFECTINSTANCE * pEffectInstances, 
	DWORD NumMaterials, 
	CONST DWORD * pAdjacency, 
	LPD3DXSKININFO pSkinInfo, 
	LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	return E_NOTIMPL;
}

HRESULT Hierachy_Loader::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	return E_NOTIMPL;
}

HRESULT Hierachy_Loader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	return E_NOTIMPL;
}
