#include "..\Header\NaviCell.h"
#include "NaviPoint.h"
#include "..\..\Reference\Header\DeviceManager.h"
#include "LineManager.h"



NaviCell::NaviCell()
{
	//m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	//assert(L"Device is null at NaviMesh"&& m_pDX9_Device);

	//D3DXCreateLine(m_pDX9_Device, &m_pDX9_Line);
	//assert(L"Line Com is null at NaviMesh" && m_pDX9_Line);

}


NaviCell::~NaviCell()
{
}

void NaviCell::Initialize()
{
}

//void NaviCell::Render()
//{
//	Vector3		vPoint[4];
//
//	vPoint[0] = m_arrNaviPoints[0]->Get_Position();
//	vPoint[1] = m_arrNaviPoints[1]->Get_Position();
//	vPoint[2] = m_arrNaviPoints[2]->Get_Position();
//	vPoint[3] = m_arrNaviPoints[0]->Get_Position();
//
//	Matrix		matViewSpcae, matProjSpace, matTemp;
//
//	D3DXMatrixIdentity(&matTemp);
//	m_pDX9_Device->GetTransform(D3DTS_VIEW, &matViewSpcae);
//	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &matProjSpace);
//
//	for (int i = 0; i < 4; ++i)
//	{
//		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matViewSpcae);
//
//		if (vPoint[i].z <= 0.1f)
//		{
//			vPoint[i].z == 0.1f;
//		}
//
//		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matProjSpace);
//
//	}
//
//	m_pDX9_Line->SetWidth(3.f);
//
//	m_pDX9_Line->Begin();
//
//	m_pDX9_Line->DrawTransform(vPoint, 4, &matTemp, D3DCOLOR_RGBA(0, 255, 0, 255));
//
//	m_pDX9_Line->End();
//
//}

void NaviCell::Release()
{
}

void NaviCell::Setup_Lines()
{
	D3DXCOLOR colorTemp = D3DCOLOR_RGBA(0, 255, 0, 255);

	if (m_arrNaviPoints[0] != nullptr && m_arrNaviPoints[1] != nullptr)
	{
		LineManager::Get_Instance()->Insert_Line(
			LineManager::Get_Instance()->Create_Line(
			m_arrNaviPoints[0]->Get_Position(),
			m_arrNaviPoints[1]->Get_Position(),
			colorTemp));

		if (m_arrNaviPoints[2] != nullptr)
		{
			LineManager::Get_Instance()->Insert_Line(
				LineManager::Get_Instance()->Create_Line(
					m_arrNaviPoints[1]->Get_Position(),
					m_arrNaviPoints[2]->Get_Position(),
					colorTemp));

			LineManager::Get_Instance()->Insert_Line(
				LineManager::Get_Instance()->Create_Line(
					m_arrNaviPoints[2]->Get_Position(), 
					m_arrNaviPoints[0]->Get_Position(),
					colorTemp));
		}
	}


}

NaviPoint * NaviCell::Get_NaviPoint(int _iIndex)
{
	return m_arrNaviPoints[_iIndex];
}

int NaviCell::Get_PointArraySize()
{
	int iSize = 0;

	for (int i = 0; i < 3; ++i)
	{
		if (m_arrNaviPoints[i] != nullptr)
		{
			++iSize;
		}
	}

	return iSize;
}

HRESULT NaviCell::Insert_NaviPoint(NaviPoint * _pPoint, int _iIndex)
{
	if (m_arrNaviPoints[_iIndex] == nullptr)
	{
		m_arrNaviPoints[_iIndex] = _pPoint;

		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}
 