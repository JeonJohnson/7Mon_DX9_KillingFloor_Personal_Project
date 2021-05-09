#pragma once

#ifndef _NAVI_CELL_H_
#define _NAVI_CELL_H_

#include "Engine_Include.h"

class NaviPoint;

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



public: /* Get */
	NaviPoint*			Get_NaviPoint(int _iIndex);
	int					Get_PointArraySize();
	NaviCell*			Get_AdjacencyCell(int _iIndex);

public: /* Set */
	HRESULT	Insert_NaviPoint(NaviPoint* _pPoint, int _iIndex);
	void	Set_AdjacencyCell(int iIndex, NaviCell* _pNaviMesh);

private:
	//LPDIRECT3DDEVICE9	m_pDX9_Device = nullptr;
	//LPD3DXLINE			m_pDX9_Line = nullptr;
	NaviPoint*			m_arrNaviPoints[3] = { nullptr };
	NaviCell*			m_AdjacencyCell[3] = { nullptr };

};

#endif //_NAVI_CELL_H_