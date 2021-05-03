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

public:

public:

private:
	vector<NaviCell*>		m_vecNaviCells;

};

#endif //_NAVI_MESH_H_