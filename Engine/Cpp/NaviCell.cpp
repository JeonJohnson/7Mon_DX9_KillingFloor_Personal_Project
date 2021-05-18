#include "..\Header\NaviCell.h"
#include "NaviPoint.h"
#include "DeviceManager.h"
#include "LineManager.h"
#include "Line.h"


NaviCell::NaviCell()
{
	//m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	//assert(L"Device is null at NaviMesh"&& m_pDX9_Device);

	//D3DXCreateLine(m_pDX9_Device, &m_pDX9_Line);
	//assert(L"Line Com is null at NaviMesh" && m_pDX9_Line);

}


NaviCell::~NaviCell()
{
	Release();
}

void NaviCell::Initialize()
{
}

//void NaviCell::Render()
//{
//	Vector3		vPoint[4];
//
//	vPoint[0] = m_arrNaviPoints[0]->Get_Position();
//	vPoint[1] = m_arrNaviPoints[1]->Get_Position();
//	vPoint[2] = m_arrNaviPoints[2]->Get_Position();
//	vPoint[3] = m_arrNaviPoints[0]->Get_Position();
//
//	Matrix		matViewSpcae, matProjSpace, matTemp;
//
//	D3DXMatrixIdentity(&matTemp);
//	m_pDX9_Device->GetTransform(D3DTS_VIEW, &matViewSpcae);
//	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &matProjSpace);
//
//	for (int i = 0; i < 4; ++i)
//	{
//		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matViewSpcae);
//
//		if (vPoint[i].z <= 0.1f)
//		{
//			vPoint[i].z == 0.1f;
//		}
//
//		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matProjSpace);
//
//	}
//
//	m_pDX9_Line->SetWidth(3.f);
//
//	m_pDX9_Line->Begin();
//
//	m_pDX9_Line->DrawTransform(vPoint, 4, &matTemp, D3DCOLOR_RGBA(0, 255, 0, 255));
//
//	m_pDX9_Line->End();
//
//}

void NaviCell::Release()
{

}

void NaviCell::Setup_Lines()
{
	D3DXCOLOR colorTemp = D3DCOLOR_RGBA(0, 255, 0, 255);

	if (m_arrNaviPoints[0] != nullptr && m_arrNaviPoints[1] != nullptr)
	{
		LineManager::Get_Instance()->Insert_Line(
			m_ArrLines[0] = LineManager::Get_Instance()->Create_Line(
			m_arrNaviPoints[0]->Get_Position(),
			m_arrNaviPoints[1]->Get_Position(),
			colorTemp));

		m_ArrLines[0]->Setup_Normal();
		//m_Lines[0] = make_pair(m_arrNaviPoints[0]->Get_Position(), m_arrNaviPoints[1]->Get_Position());

		if (m_arrNaviPoints[2] != nullptr)
		{
			LineManager::Get_Instance()->Insert_Line(
				m_ArrLines[1] = LineManager::Get_Instance()->Create_Line(
					m_arrNaviPoints[1]->Get_Position(),
					m_arrNaviPoints[2]->Get_Position(),
					colorTemp));
			m_ArrLines[1]->Setup_Normal();
			//m_Lines[1] = make_pair(m_arrNaviPoints[1]->Get_Position(), m_arrNaviPoints[2]->Get_Position());

			LineManager::Get_Instance()->Insert_Line(
				m_ArrLines[2] = LineManager::Get_Instance()->Create_Line(
					m_arrNaviPoints[2]->Get_Position(), 
					m_arrNaviPoints[0]->Get_Position(),
					colorTemp));
			m_ArrLines[2]->Setup_Normal();
			//m_Lines[2] = make_pair(m_arrNaviPoints[2]->Get_Position(), m_arrNaviPoints[0]->Get_Position());

		}
	}
}

bool NaviCell::Setting_AdjacencyCell(NaviPoint * _pointA, NaviPoint * _pointB, NaviCell * _pCell)
{

	if (m_arrNaviPoints[POINT_A] == _pointA)
	{
		if (m_arrNaviPoints[POINT_B] == _pointB)
		{//다음 번 셀의 A와 B Point가 지금 이 셀의 A와 B Point랑 같을 경우.
			m_AdjacencyCell[CELL_AB] = _pCell;
			return true;
		}

		if (m_arrNaviPoints[POINT_C] == _pointB)
		{
			m_AdjacencyCell[CELL_CA] = _pCell;
			return true;
		}
	}

	if (m_arrNaviPoints[POINT_B] == _pointA)
	{
		if (m_arrNaviPoints[POINT_A] == _pointB)
		{
			m_AdjacencyCell[CELL_AB] = _pCell;
			return true;
		}

		if (m_arrNaviPoints[POINT_C] == _pointB)
		{
			m_AdjacencyCell[CELL_BC] = _pCell;
			return true;
		}
	}

	if (m_arrNaviPoints[POINT_C] == _pointA)
	{
		if (m_arrNaviPoints[POINT_B] == _pointB)
		{
			m_AdjacencyCell[CELL_BC] = _pCell;
			return true;
		}

		if (m_arrNaviPoints[POINT_A] == _pointB)
		{
			m_AdjacencyCell[CELL_CA] = _pCell;
			return true;
		}
	}

	return false;
	

	///return false;
}

Cell_Option NaviCell::Compare(const Vector3 & _vEndPos, int* pOutIndex)
{
	for (int i = 0; i < 3; ++i)
	{
		if (m_ArrLines[i]->Compare(_vEndPos) == Line_Dir::LINE_LEFT)
		{
			if (m_AdjacencyCell[i] == nullptr)
			{
				return Cell_Option::CELL_STOP;
			}
			else
			{
				*pOutIndex = m_AdjacencyCell[i]->Get_CellIndex();
				return Cell_Option::CELL_MOVE;
			}
		}
	}

	return Cell_Option::CELL_MOVE;
}




NaviPoint * NaviCell::Get_NaviPoint(int _iIndex)
{
	return m_arrNaviPoints[_iIndex];
}

int NaviCell::Get_PointArraySize()
{
	int iSize = 0;

	for (int i = 0; i < 3; ++i)
	{
		if (m_arrNaviPoints[i] != nullptr)
		{
			++iSize;
		}
	}

	return iSize;
}

NaviCell * NaviCell::Get_AdjacencyCell(int _iIndex)
{
	if (_iIndex > 2)
	{
		return nullptr;
	}
	return m_AdjacencyCell[_iIndex];
}

int NaviCell::Get_CellIndex()
{
	return m_iCellIndex;
}

HRESULT NaviCell::Insert_NaviPoint(NaviPoint * _pPoint, int _iPointIndex)
{
	if (m_arrNaviPoints[_iPointIndex] == nullptr)
	{
		m_arrNaviPoints[_iPointIndex] = _pPoint;

		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}

void NaviCell::Set_AdjacencyCell(int iIndex, NaviCell * _pNaviMesh)
{
	m_AdjacencyCell[iIndex] = _pNaviMesh;
}

void NaviCell::Set_CellIndex(int _iIndex)
{
	m_iCellIndex = _iIndex;
}
 