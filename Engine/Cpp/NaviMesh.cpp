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

			//�̿��ϴ� ���� ����
			//�� ���� �� ���� ���ؼ� �̿��ϸ� �̿��ϴ� �� ����.
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

vector<NaviCell*> NaviMesh::Get_NaivCellList()
{
	return m_vecNaviCells;
}

void NaviMesh::Insert_NaviCell(NaviCell * _pNaviCell)
{
	m_vecNaviCells.emplace_back(_pNaviCell);
}
