#include "stdafx.h"
#include "..\Header\ShakeObject.h"


ShakeObject::ShakeObject(Desc * _desc)
{
	//m_fDuringTime = _desc->fDuring;
	m_fInterval = _desc->fInterval;
	m_fPower = _desc->fPower;
	m_iCount = _desc->iCount;
}

ShakeObject::~ShakeObject()
{
}

void ShakeObject::Initialize()
{
	m_vStartPos = m_Transform->Get_Position();
}

void ShakeObject::Update()
{
	if (m_iCount == 0)
	{
		return;
	}

	m_fTime += fTime;

	if (m_fTime >= m_fInterval)
	{
		--m_iCount;
		m_fTime -= m_fInterval;

		if (m_iCount % 2 == 0)
		{
			m_Transform->Set_Position(m_vStartPos);
		}
		else 
		{
			float RandX, RandY;
			RandX = ((rand() % 201) - 100) / 100.f;
			RandY = ((rand() % 201) - 100) / 100.f;

			Vector3 Offset = { RandX, RandY, 0.f };

			Vector3	Offset_Normal;
			D3DXVec3Normalize(&Offset_Normal, &Offset);
			Offset =  Offset_Normal* m_fPower;

			m_Transform->Add_Position(Offset);
		}

		if (m_iCount == 0)
		{
			m_Transform->Set_Position(m_vStartPos);
		}
	}

	

}

void ShakeObject::LateUpdate()
{
}

void ShakeObject::ReadyRender()
{
}

void ShakeObject::Release()
{
}

void ShakeObject::Shaking(float _fPower, int _iCount, float _fInterval)
{
	m_vStartPos = m_Transform->Get_Position();
	m_fPower = _fPower;
	m_iCount = _iCount;
	m_fInterval = _fInterval;
}
