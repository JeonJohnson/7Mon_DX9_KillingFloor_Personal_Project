#include "..\Header\NaviMesh.h"
#include "DeviceManager.h"

#include "NaviCell.h"

NaviMesh::NaviMesh()
{

}


NaviMesh::~NaviMesh()
{
	Release();
}

void NaviMesh::Initialize()
{
}

void NaviMesh::Release()
{
	for (auto& cell : m_vecNaviCells)
	{
		Safe_Delete(cell);
	}
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

			//?̿??ϴ? ???? ????
			//?? ???? ?? ???? ?????ؼ? ?̿??ϸ? ?̿??ϴ? ?? ????.
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


Vector3 NaviMesh::MoveOn(const Vector3 & _vTargetPos, const Vector3 & _vTargetDir, int* _pOutCurCellIndex)
{
	Vector3 vEndPos = _vTargetPos + _vTargetDir;

	if (m_vecNaviCells[*_pOutCurCellIndex]->Compare(vEndPos, _pOutCurCellIndex) == CELL_MOVE)
	{
		return vEndPos;
	}
	//else if (m_vecNaviCells[m_iCellIndex]->Compare(vEndPos, &m_iCellIndex) == CELL_STOP)
	//{
		return _vTargetPos;
	//}

}

Vector3 NaviMesh::Add_Pos(const Vector3 & _vCurPos, const Vector3 & _vAddPos, int* _pOutCurCellIndex)
{
	Vector3 vAddPos = _vAddPos;
	Vector3 vEndPos = _vCurPos + _vAddPos;
	Vector3 vNone = { 0.f, 0.f, 0.f };

	if (m_vecNaviCells[*_pOutCurCellIndex]->Compare(vEndPos, _pOutCurCellIndex) == CELL_MOVE)
	{
		return vAddPos;
	}
	return vNone;
}

//void NaviMesh::Cells_Update()
//{
//	for (auto& cell : m_vecNaviCells)
//	{
//		cell->Setup_Lines();
//	}
//}

vector<NaviCell*> NaviMesh::Get_NaivCellList()
{
	return m_vecNaviCells;
}

void NaviMesh::Insert_NaviCell(NaviCell * _pNaviCell)
{
	m_vecNaviCells.emplace_back(_pNaviCell);
}
