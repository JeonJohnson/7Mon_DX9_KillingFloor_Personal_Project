#pragma once

#ifndef _NAVI_CELL_H_
#define _NAVI_CELL_H_

#include "Engine_Include.h"

class NaviPoint;
class Line;

class DLL_STATE NaviCell
{
	friend class NaviMesh;
public:

public:
	NaviCell();
	~NaviCell();

public:
	void Initialize();
	//void Render();
	void Release();

public:

public: /* Func */
	void Setup_Lines();


	bool Setting_AdjacencyCell(NaviPoint*_pointA, NaviPoint* _pointB, NaviCell* _pCell);
	//Mesh에서 이 Cell의 다음번 Cell의 Point를 넣어서
	//같은 값이 있는 곳 방향에다가 인접시켜줌.

	Cell_Option		Compare(const Vector3& _vEndPos, int* pOutIndex);
	//ㄹㅇ 인접한곳이 갈 수 있는 곳인지 아닌지 확인하기 위한 용도.


public: /* Get */
	NaviPoint*			Get_NaviPoint(int _iIndex);
	int					Get_PointArraySize();
	NaviCell*			Get_AdjacencyCell(int _iIndex);
	int					Get_CellIndex();

public: /* Set */
	HRESULT	Insert_NaviPoint(NaviPoint* _pPoint, int _iPointIndex);
	void	Set_AdjacencyCell(int iIndex, NaviCell* _pNaviMesh);
	void	Set_CellIndex(int _iIndex);

private:
	//LPDIRECT3DDEVICE9	m_pDX9_Device = nullptr;
	//LPD3DXLINE			m_pDX9_Line = nullptr;
	int					m_iCellIndex;
	NaviPoint*			m_arrNaviPoints[3] = { nullptr };
	NaviCell*			m_AdjacencyCell[3] = { nullptr };
	Line*				m_ArrLines[3] = { nullptr };
};

#endif //_NAVI_CELL_H_