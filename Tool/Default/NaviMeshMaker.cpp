#include "stdafx.h"
#include "NaviMeshMaker.h"

NaviMeshMaker::NaviMeshMaker(Desc * _desc)
{
}

NaviMeshMaker::~NaviMeshMaker()
{
}

void NaviMeshMaker::Initialize()
{
}

void NaviMeshMaker::Update()
{
	if (MouseUp(KEY_STATE_LMouse) && g_pNaviMeshTool_Dialog->m_bPointCreate
		&& KeyPress(KEY_STATE_LCtrl))
	{
		if (g_pDefaultView->m_tMousePos_View.x >= 0)
		{
			m_tMousePos.x = (FLOAT)g_pDefaultView->m_tMousePos_View.x;
			m_tMousePos.y = (FLOAT)g_pDefaultView->m_tMousePos_View.y;

			m_vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_tMousePos, 100);
			//m_vWorldPos.y = 0.f;

			g_pNaviMeshTool_Dialog->Create_NaviPoint(m_vWorldPos);
			
		}
	}
}

void NaviMeshMaker::LateUpdate()
{

}

void NaviMeshMaker::ReadyRender()
{
}

void NaviMeshMaker::Release()
{
}
