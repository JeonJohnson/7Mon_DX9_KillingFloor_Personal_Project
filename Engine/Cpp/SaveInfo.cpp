#include "..\Header\SaveInfo.h"
#include "Function_String.h"
#include "Transform.h"


SaveInfo::SaveInfo(Desc * _desc)
{
	//m_pTerrainSave = _desc->tSaveInfo;

	ZeroMemory(&m_pTerrainSave, sizeof(Save_TerrainLayout));

	Function_String::wstring2TCHAR(_desc->szMeshPath, m_pTerrainSave.szMeshPath);
	Function_String::wstring2TCHAR(_desc->szObjName, m_pTerrainSave.szObjName);

	m_pTerrainSave.iRenderLayer = _desc->iRenderLayer;

}

SaveInfo::~SaveInfo()
{
}

void SaveInfo::Initialize()
{
}

void SaveInfo::Update()
{
	m_pTerrainSave.vPosition	= m_Transform->Get_Position();
	m_pTerrainSave.vScale = m_Transform->Get_Scale();
	m_pTerrainSave.vRotation = m_Transform->Get_Rotation_Euler();
}

void SaveInfo::LateUpdate()
{
}

void SaveInfo::ReadyRender()
{
}

void SaveInfo::Release()
{
	//Safe_Delete(m_pTerrainSave);
}

Save_TerrainLayout SaveInfo::Get_TerrainSave() const
{
	
	return m_pTerrainSave;

}
