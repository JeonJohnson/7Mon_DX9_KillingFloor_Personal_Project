#include "..\Header\NaviMesh.h"
#include "..\..\Reference\Header\DeviceManager.h"

#include "NaviCell.h"


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

void NaviMesh::Link_Cells()
{
	for (int i = 0; i < (int)m_vecNaviCells.size(); ++i)
	{
		for (int j = 0; j < (int)m_vecNaviCells.size(); ++j)
		{
			if (i == j)
			{
				continue;
			}

			//ÀÌ¿ôÇÏ´Â ¼¿ÀÌ ¾ø°í
			//ÇÑ ¼¿ÀÇ µÎ Á¡°ú ºñ±³ÇØ¼­ ÀÌ¿ôÇÏ¸é ÀÌ¿ôÇÏ´Â ¼¿ ¼³Á¤.
			if(m_vecNaviCells[i]->Get_AdjacencyCell(CELL_AB) == nullptr
				&& m_vecNaviCells[j]->Setting_AdjacencyCell(
					m_vecNaviCells[i]->Get_NaviPoint(POINT_A),
					m_vecNaviCells[i]->Get_NaviPoint(POINT_B),
					m_vecNaviCells[i]))
			{
				m_vecNaviCells[i]->Set_AdjacencyCell(CELL_AB, m_vecNaviCells[j]);
				continue;
			}
		
			if (m_vecNaviCells[i]->Get_AdjacencyCell(CELL_BC) == nullptr
				&& m_vecNaviCells[j]->Setting_AdjacencyCell(
					m_vecNaviCells[i]->Get_NaviPoint(POINT_B),
					m_vecNaviCells[i]->Get_NaviPoint(POINT_C),
					m_vecNaviCells[i]))
			{
				m_vecNaviCells[i]->Set_AdjacencyCell(CELL_BC, m_vecNaviCells[j]);
				continue;
			}

			if (m_vecNaviCells[i]->Get_AdjacencyCell(CELL_CA) == nullptr
				&& m_vecNaviCells[j]->Setting_AdjacencyCell(
					m_vecNaviCells[i]->Get_NaviPoint(POINT_C),
					m_vecNaviCells[i]->Get_NaviPoint(POINT_A),
					m_vecNaviCells[i]))
			{
				m_vecNaviCells[i]->Set_AdjacencyCell(CELL_CA, m_vecNaviCells[j]);
				continue;
			}
			

		}
		
	}

}

Vector3 NaviMesh::MoveOn(const Vector3 & _vTargetPos, const Vector3 & _vTargetDir)
{
	Vector3 vEndPos = _vTargetPos + _vTargetDir;

	if (m_vecNaviCells[m_iCellIndex]->Compare(vEndPos, &m_iCellIndex) == CELL_MOVE)
	{
		return vEndPos;
	}
	//else if (m_vecNaviCells[m_iCellIndex]->Compare(vEndPos, &m_iCellIndex) == CELL_STOP)
	//{
		return _vTargetPos;
	//}

}

vector<NaviCell*> NaviMesh::Get_NaivCellList()
{
	return m_vecNaviCells;
}

void NaviMesh::Insert_NaviCell(NaviCell * _pNaviCell)
{
	m_vecNaviCells.emplace_back(_pNaviCell);
}
