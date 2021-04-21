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
	

public: /* General */
	/* Function */
	Vector3		QuaternionToEuler(Quaternion _quaternion);
	Quaternion	EulerToQuternion(Vector3 _eulerVector);
	/* Get */


	/* Set */
	virtual void Set_Transform(Transform* _pTransform) override;
	


public: /* Matrix */
	/* Function */
	void Update_WorldMatrix();

	/* Get */
	const Matrix&		Get_WorldMatrix() const;

	/* Set */
	void				Set_WorldMatrix(const Matrix& _world);

public: /* Vector */
	/* Function */

	/* Get */
	Vector3	Get_Right();
	Vector3	Get_Up();
	Vector3	Get_Forward();

	/* Set */

public: /* Scale */
	/* Function */

	/* Get */
	const Vector3&		Get_Scale() const;

	/* Set */
	void				Set_Scale(const Vector3& _vScale); 
	void				Add_Scale(const Vector3& _vScale);
	void				Add_ScaleX(float _x);
	void				Add_ScaleY(float _y);
	void				Add_ScaleZ(float _z);

public: /* Rotation */
	/* Function */

	/* Get */
	const Quaternion&	Get_Rotation() const;
	Vector3				Get_Rotation_Euler();
	void Get_RotationX(Vector3* _pOut, Vector3 _In);
	void Get_RotationY(Vector3* _pOut, Vector3 _In);
	void Get_RotationZ(Vector3* _pOut, Vector3 _In);
	
	/* Set */
	void Set_Rotation(const Quaternion& _quaternion);
	void Set_Rotation(const Vector3& _eulerVector);
	void Set_Rotation(float _eulerX, float _eulerY, float _eulerZ);
	void Set_RotationX(float _eulerX);
	void Set_RotationY(float _eulerY);
	void Set_RotationZ(float _eulerZ);
	void Rotate(const Vector3& _eulerVector);
	void RotateX(float _eulerX);
	void RotateY(float _eulerY);
	void RotateZ(float _eulerZ);
	//void RotateRollPitchYaw(float _x, float _y, float _z);
	void RotateAxis(const Vector3& _axis, float _radian, Quaternion* _pOut);
	void RotateAxis(const Vector3& _axis, float _radian);


public: /* Transform(position) */
	/* Function */

	/* Get */
	const Vector3&		Get_Position() const;


	/* Set */
	void				Set_Position(const Vector3& _vPos);
	void				Add_Position(const Vector3& _vPos);
	void				Add_PosX(float _x);
	void				Add_PosY(float _y);
	void				Add_PosZ(float _z);

private:
	Matrix		m_matWorldMatrix;
	Vector3		m_vPosition = { 0.f, 0.f, 0.f };
	Vector3		m_vScale = { 1.f, 1.f, 1.f };
	Quaternion	m_qRotation = { 0.f, 0.f,0.f,1.f };
	//Vector3		m_vRotation = { 0.f,0.f,0.f };
	


};


#endif //_TRANSFORM_H_

