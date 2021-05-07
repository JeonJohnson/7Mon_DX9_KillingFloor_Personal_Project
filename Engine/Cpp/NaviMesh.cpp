#include "..\Header\NaviMesh.h"
#include "..\..\Reference\Header\DeviceManager.h"



NaviMesh::NaviMesh()
{

}


NaviMesh::~NaviMesh()
{
}

void NaviMesh::Initialize()
{
}

void NaviMesh::Release()
{
}

vector<NaviCell*> NaviMesh::Get_NaivCellList()
{
	return m_vecNaviCells;
}

void NaviMesh::Insert_NaviCell(NaviCell * _pNaviCell)
{
	m_vecNaviCells.emplace_back(_pNaviCell);
}
