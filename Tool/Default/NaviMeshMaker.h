#pragma once


#include "Tool_Include.h"

#include "Component.h"


class NaviMeshMaker :	public Component
{
public:
	struct Desc
	{


	};

public:
	explicit	NaviMeshMaker(Desc* _desc);
	virtual		~NaviMeshMaker();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void		Create_Point();

public:

	void		Picking_Mesh();
	bool		Picking_Ray2Sphere(GameObject** _PickingObject, 
		float* _fpOutDistance = nullptr,
		Vector3* _vpOutIntersection = nullptr);

	void		Create_Ray(const Vector2& _ScreenPos);

private:
	Vector2		m_tMousePos;
	Vector3		m_vWorldPos;

	//for meshpicking

	GameObject*		m_pSelectSphere[2] = {nullptr};
	Vector3			m_vRayOrigin; //2뷰스페이스
	Vector3			m_vRayDir; //2월드
	//크릭한 곳에서 부터 화면 안쪽으로 향하는 광선의 방향
};

