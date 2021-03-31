#pragma once

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Engine_Define.h"

#include "Component.h"

class DLL_STATE Transform : public Component
{
public:
	struct Desc
	{

	};

public:
	Transform(Desc* _desc);
	~Transform();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public: /* Matrix */
	void Update_WorldMatrix();

public: /* Scale */
	

public: /* Rotation */
	void Get_RotationX(Vector3* _pOut, Vector3 _In);
	void Get_RotationY(Vector3* _pOut, Vector3 _In);
	void Get_RotationZ(Vector3* _pOut, Vector3 _In);

public: /* Transform(position) */

public: /* Get */
	const Vector3&		Get_Position() const;
	const Vector3&		Get_Scale() const;
	const Quaternion&	Get_Rotation() const;


public: /* Set */ 



public: /* Functions */


public:
	Vector3		m_vPosition	= { 0.f, 0.f, 0.f };
	Vector3		m_vScale = { 1.f, 1.f, 1.f };
	Quaternion	m_qRotation = { 0.f, 0.f,0.f,1.f };

private:
	Matrix		m_matWorldMatrix;
	



};


#endif //_TRANSFORM_H_