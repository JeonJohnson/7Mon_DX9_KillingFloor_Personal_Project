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

	Line::Desc lineDesc;
	lineDesc.fWidth = 10.f;
	lineDesc.vStart = Vector3(0 , 0, 0);
	lineDesc.vDest = Vector3(100, 100, 100);
	Line*	pLineTemp = new Line(&lineDesc);
	Insert_Line(pLineTemp);

}

void LineManager::Render()
{
	Matrix	matViewSpace, matProjSpace;

	m_pDX9_Device->GetTransform(D3DTS_VIEW, &matViewSpace);
	m_pDX9_Device->GetTransform(D3DTS_PROJECTION, &matProjSpace);
	
	//m_pDX9_Device->EndScene();
	//m_pDX9_Device->BeginScene();

	for (auto& line : m_listLines)
	{
		Vector3 vPos[2];
		vPos[0]= line->Get_StartPos();
		vPos[1] = line->Get_DestPos();

		for (int i = 0; i < 2; ++i)
		{
			D3DXVec3TransformCoord(&vPos[i], &vPos[i], &matViewSpace);
			if (vPos[i].z <= 0.1f)
			{
				vPos[i].z == 0.1f;
			}
			//D3DXVec3TransformCoord(&vPos[i], &vPos[i], &matProjSpace);
		}

		Matrix matTemp;
		D3DXMatrixIdentity(&matTemp);
		//matTemp = matTemp * matViewSpace * matProjSpace;

		m_pDX9_LineCom->SetWidth(20.f);

		m_pDX9_LineCom->Begin();
		HRESULT hTemp = m_pDX9_LineCom->DrawTransform(vPos, 2, &matProjSpace, line->Get_Color());
		if (hTemp == E_FAIL)
		{
			int i = 0;
		}
		m_pDX9_LineCom->End();
	}


}

void LineManager::Release()
{

	Safe_Release(m_pDX9_LineCom);
}

void LineManager::Delete_Lines()
{
	
}

void LineManager::Insert_Line(Line * _pLine)
{
	assert(L"Line is null" && _pLine);

	m_listLines.emplace_back(_pLine);
}
