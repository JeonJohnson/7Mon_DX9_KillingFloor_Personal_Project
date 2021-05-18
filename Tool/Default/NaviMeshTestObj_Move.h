#pragma once


#include "Component.h"

class NaviMesh;

class NaviMeshTestObj_Move : public Component
{
public:
	struct Desc
	{
		
	};

public:
	NaviMeshTestObj_Move(Desc* _desc);
	virtual ~NaviMeshTestObj_Move();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void Move();

public:
	
public:

public:
	void		Set_NaviMesh(NaviMesh* _pNaviMesh);


private:
	NaviMesh*		m_pNaviMesh = nullptr;
	int				m_iCurCellIndex = 0;
};
