#include "..\Header\LineManager.h"
#include "DeviceManager.h"

Implement_Singleton(LineManager)

LineManager::LineManager()
{
}


LineManager::~LineManager()
{
}

void LineManager::Initialize()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

	D3DXCreateLine(m_pDX9_Device, &m_pDX9_LineCom);

	//Line::Desc lineDesc;
	//lineDesc.fWidth = 10.f;
	//lineDesc.vStart = Vector3(0 , 0, 0);
	//lineDesc.vDest = Vector3(100, 100, 100);
	//Line*	pLineTemp = new Line(&lineDesc);
	//Insert_Line(pLineTemp);

}

void LineManager::Render()
{
#ifdef _DEBUG
	Vector3		vPos[2];
	//D3DCOLOR	tColor;
	//float		fWidth;
	Matrix		matViewSpace, matProjSpace, matTemp;

	m_pDX9_Device->GetTransform(D3DTS_VIEW, &matViewSpace);
	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &matProjSpace);

	for (auto& line : m_listLines)
	{
		vPos[0] = line->Get_StartPos();
		vPos[1] = line->Get_DestPos();

		for (int i = 0; i < 2; ++i)
		{
			D3DXVec3TransformCoord(&vPos[i], &vPos[i], &matViewSpace);
			if (vPos[i].z <= 0.1f)
			{
				vPos[i].z = 0.1f;
			}
			D3DXVec3TransformCoord(&vPos[i], &vPos[i], &matProjSpace);
		}

		D3DXMatrixIdentity(&matTemp);

		m_pDX9_LineCom->SetWidth(line->Get_Width());

		m_pDX9_LineCom->Begin();
		m_pDX9_LineCom->DrawTransform(vPos, 2, &matTemp, line->Get_Color());
		m_pDX9_LineCom->End();
	}
#endif //_DEBUG
}

void LineManager::Release()
{
	Delete_Lines();

	Safe_Release(m_pDX9_LineCom);
}

void LineManager::Delete_Lines()
{
	
	for (auto list_iter = m_listLines.begin(); list_iter != m_listLines.end();)
	{
		(*list_iter)->Release();
		delete *list_iter;
		*list_iter = nullptr;
		list_iter = m_listLines.erase(list_iter);
	}

}

Line * LineManager::Create_Line(const Vector3& _vStart,
	const Vector3& _vDest,  D3DXCOLOR _tColor, float _fWidth)
{
	Line::Desc	descTemp;
	descTemp.vStart = _vStart;
	descTemp.vDest = _vDest;
	descTemp.tColor = _tColor;
	descTemp.fWidth = _fWidth;

	Line*	LineTemp = new Line(&descTemp);

	return LineTemp;
}

void LineManager::Insert_Line(Line * _pLine)
{
	assert(L"Line is null" && _pLine);

	m_listLines.emplace_back(_pLine);
}
