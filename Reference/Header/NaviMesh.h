#pragma once

#ifndef _NAVI_MESH_H_
#define _NAVI_MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class NaviCell;
class NaviPoint;

class DLL_STATE NaviMesh : public CResource
{
public:
	NaviMesh();
	virtual ~NaviMesh();

public:
	virtual void Initialize() override;
	
	virtual void Release() override;

public:

public:
	void		Link_Cells();
	Vector3		MoveOn(const Vector3& _vTargetPos, const Vector3& _vTargetDir);
	
	Vector3		Add_Pos(const Vector3& _vCurPos, const Vector3&	_vAddPos);

public: /* Get */
	vector<NaviCell*>	Get_NaivCellList();

public: /* Set */
	void		Insert_NaviCell(NaviCell* _pNaviCell);

private:
	vector<NaviCell*>		m_vecNaviCells;
	int						m_iCellIndex = 0;//플레이어가 위치해 있는 인덱스?
};

#endif //_NAVI_MESH_H_