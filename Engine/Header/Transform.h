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
		Vector3		vPos = { 0.f,0.f,0.f };
		Vector3		vScale = { 1.f, 1.f, 1.f };
		Quaternion	qRotation = { 0.f,0.f,0.f,1.f };
	};

public:
	explicit Transform(Desc* _desc);
	explicit Transform();
	virtual ~Transform();

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
	const Matrix&		Get_WorldMatrix() const;
	const Vector3&		Get_Position() const;
	const Vector3&		Get_Scale() const;
	const Quaternion&	Get_Rotation() const;
	const Vector3&		Get_Rotation_Euler() const;

public: /* Set */ 



public: /* Functions */
	void QuaternionToEuler(Quaternion* qIn, Vector3* qOut);


public:


private:
	Matrix		m_matWorldMatrix;
	Vector3		m_vPosition = { 0.f, 0.f, 0.f };
	Vector3		m_vScale = { 1.f, 1.f, 1.f };
	Quaternion	m_qRotation = { 0.f, 0.f,0.f,1.f };
	//Vector3		m_vRotation = { 0.f,0.f,0.f };
	


};


#endif //_TRANSFORM_H_