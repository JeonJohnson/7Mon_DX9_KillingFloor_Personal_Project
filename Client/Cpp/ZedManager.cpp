#include "stdafx.h"
#include "..\Header\ZedManager.h"
#include "AnimationController.h"
#include "SphereCollider.h"
#include "HudManager.h"
#include "Zed_Status.h"
#include "..\..\Engine\Header\StateController.h"
#include "Zed_Idle.h"
#include "Zed_Walk.h"
#include "Zed_Run.h"
#include "Zed_Att.h"
#include "Zed_Hit.h"
#include "Zed_Death.h"
#include "Zed.h"

ZedManager* ZedManager::m_pInstance = nullptr;

ZedManager::ZedManager(Desc * _desc)
{
}

ZedManager::~ZedManager()
{
}

ZedManager * ZedManager::Get_Instance()
{
	if (m_pInstance == nullptr)
	{
		auto mgrObj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"ZedManager");
		mgrObj->Add_Component<ZedManager>();

		m_pInstance = mgrObj->Get_Component<ZedManager>();
	}

	return m_pInstance;
}

void ZedManager::Destroy_Instance()
{
	if (m_pInstance)
	{
		GameObject::Destory(m_pInstance->Get_GameObject());
	}
}

void ZedManager::Initialize()
{
	Nogada_Datas();
}

void ZedManager::Update()
{
	HudManager::Get_Instance()->Set_TextZedCount(m_iZedCount);

	//if (KeyDown(KEY_STATE_F1))
	//{
	//	Generate_Clot(Vector3(0.f, 0.f,100.f));
	//}

	//if (KeyDown(KEY_STATE_F2))
	//{
	//	Generate_GoreFast(Vector3(50.f, 0.f, 100.f));
	//}

	//if (KeyDown(KEY_STATE_F3))
	//{
	//	Generate_Scrake(Vector3(100.f, 0.f, 100.f));
	//}

	//if (KeyDown(KEY_STATE_F4))
	//{
	//	Generate_Patriarch(Vector3(150.f, 0.f, 100.f));
	//}

}

void ZedManager::LateUpdate()
{
}

void ZedManager::ReadyRender()
{
}

void ZedManager::Release()
{
}

void ZedManager::Nogada_Datas()
{
	{
		arrZedInfo[ZED_Clot].m_eName = ZED_Clot;
		arrZedInfo[ZED_Clot].m_iMaxHp = 100;
		arrZedInfo[ZED_Clot].m_iCurHp = 100;
		arrZedInfo[ZED_Clot].m_fWalkSpd = 55.f;
		arrZedInfo[ZED_Clot].m_fRunSpd = 55.f;
		arrZedInfo[ZED_Clot].m_iDmg = 10;

	}

	{
		arrZedInfo[ZED_GoreFast].m_eName = ZED_GoreFast;
		arrZedInfo[ZED_GoreFast].m_iMaxHp = 200;
		arrZedInfo[ZED_GoreFast].m_iCurHp = 200;
		arrZedInfo[ZED_GoreFast].m_fWalkSpd = 60.f;
		arrZedInfo[ZED_GoreFast].m_fRunSpd = 70.f;
		arrZedInfo[ZED_GoreFast].m_iDmg = 20;
	}

	{
		arrZedInfo[ZED_Scrake].m_eName = ZED_Scrake;
		arrZedInfo[ZED_Scrake].m_iMaxHp = 400;
		arrZedInfo[ZED_Scrake].m_iCurHp = 400;
		arrZedInfo[ZED_Scrake].m_fWalkSpd = 50.f;
		arrZedInfo[ZED_Scrake].m_fRunSpd = 75.f;
		arrZedInfo[ZED_Scrake].m_iDmg = 25;
		arrZedInfo[ZED_Scrake].m_iStrongDmg = 40;

	}

	{
		arrZedInfo[ZED_Patriarch].m_eName = ZED_Patriarch;
		arrZedInfo[ZED_Patriarch].m_iMaxHp = 1500;
		arrZedInfo[ZED_Patriarch].m_iCurHp = 1500;
		arrZedInfo[ZED_Patriarch].m_fWalkSpd = 55.f;
		arrZedInfo[ZED_Patriarch].m_fRunSpd = 70.f;
		arrZedInfo[ZED_Patriarch].m_iDmg = 20;
		arrZedInfo[ZED_Patriarch].m_iStrongDmg = 50;
		arrZedInfo[ZED_Patriarch].m_iMg42Dmg = 10;
		arrZedInfo[ZED_Patriarch].m_iMissileDmg = 50;
	}

	{
		//arrZedGenLocate[CHURCH_RIGHT] = Vector3(375.f, 0.f, 212.f);
		//arrZedGenLocate[CHURCH_LEFT] = Vector3(-104.f, 0.f, 212.f);
		//arrZedGenLocate[CHURCH_RIGHT] = Vector3(320.f, 0.f, 200.f);
		//arrZedGenLocate[CHURCH_LEFT] = Vector3(-70.f, 0.f, 200.f);

		arrZedGenLocate[CHURCH_RIGHT] = Vector3(300.f, 0.f, 200.f);
		arrZedGenLocate[CHURCH_LEFT] = Vector3(-50.f, 0.f, 200.f);
		arrZedGenLocate[POLICE_RIGHT] = Vector3(285.f, 0.f, 715.f);
		arrZedGenLocate[POLICE_LEFT] = Vector3(-15.f, 0.f, 715.f);
	}

}

void ZedManager::Generate_Clot(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{

		GameObject* TestClot = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" + to_wstring(m_iZedCount));
		
		//TestClot->Set_Position(Vector3(50.f,0.f,50.f));
		TestClot->Set_Position(_vPos);
		TestClot->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));
		//TestClot->Set_Rotation(_qRot);

		TestClot->Add_Component<StateController>();
		auto ZedStateCtrl = TestClot->Get_Component<StateController>();
		ZedStateCtrl->Add_State<Zed_Idle>(L"Zed_Idle");
		ZedStateCtrl->Add_State<Zed_Walk>(L"Zed_Walk");
		ZedStateCtrl->Add_State<Zed_Run>(L"Zed_Run");
		ZedStateCtrl->Add_State<Zed_Att>(L"Zed_Att");
		ZedStateCtrl->Add_State<Zed_Hit>(L"Zed_Hit");
		ZedStateCtrl->Add_State<Zed_Death>(L"Zed_Death");
		ZedStateCtrl->Set_InitState(L"Zed_Idle");

		Mesh_Renderer::Desc Clot_Test;
		Clot_Test.szMeshName = L"Clot";
		Clot_Test.vRot = Vector3(0.f, 180.f, 0.f);
		TestClot->Add_Component<Mesh_Renderer>(&Clot_Test);

		AnimationController::Desc Clot_Anim;
		Clot_Anim.InitIndex = 0;
		Clot_Anim.bLoop = true;
		Clot_Anim.bClone = true;
		TestClot->Add_Component<AnimationController>(&Clot_Anim);

		SphereCollider::Desc Clot_Col;
		Clot_Col.fRadius = 12.5f;
		Clot_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		Clot_Col.szColName = L"Body";
		TestClot->Add_Component<SphereCollider>(&Clot_Col);
		 
		Zed::Desc Clot_Default;
		Clot_Default.tZed_Status = arrZedInfo[ZED_Clot];
		Clot_Default.pNaviMesh = EngineFunction->Get_NaviMesh(L"NaviMesh_Zeds");
		TestClot->Add_Component<Zed>(&Clot_Default);

		++m_iZedCount;

}

void ZedManager::Generate_GoreFast(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{
	
		GameObject* TestGoreFast = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" + to_wstring(m_iZedCount));
		TestGoreFast->Set_Position(_vPos);
		TestGoreFast->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));
		//TestGoreFast->Set_Rotation(_qRot);

		TestGoreFast->Add_Component<StateController>();
		auto ZedStateCtrl = TestGoreFast->Get_Component<StateController>();
		ZedStateCtrl->Add_State<Zed_Idle>(L"Zed_Idle");
		ZedStateCtrl->Add_State<Zed_Walk>(L"Zed_Walk");
		ZedStateCtrl->Add_State<Zed_Run>(L"Zed_Run");
		ZedStateCtrl->Add_State<Zed_Att>(L"Zed_Att");
		ZedStateCtrl->Add_State<Zed_Hit>(L"Zed_Hit");
		ZedStateCtrl->Add_State<Zed_Death>(L"Zed_Death");
		ZedStateCtrl->Set_InitState(L"Zed_Idle");

		Mesh_Renderer::Desc GoreFast_Mesh;
		GoreFast_Mesh.szMeshName = L"GoreFast";
		GoreFast_Mesh.vRot = Vector3(0.f, 180.f, 0.f);
		TestGoreFast->Add_Component<Mesh_Renderer>(&GoreFast_Mesh);

		AnimationController::Desc GoreFast_Anim;
		GoreFast_Anim.InitIndex = 0;
		GoreFast_Anim.bLoop = true;
		GoreFast_Anim.bClone = true;
		TestGoreFast->Add_Component<AnimationController>(&GoreFast_Anim);

		SphereCollider::Desc GoreFast_Col;
		GoreFast_Col.fRadius = 12.5f;
		GoreFast_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		GoreFast_Col.szColName = L"Body";
		TestGoreFast->Add_Component<SphereCollider>(&GoreFast_Col);

		Zed::Desc GoreFast_Default;
		GoreFast_Default.tZed_Status = arrZedInfo[ZED_GoreFast];
		GoreFast_Default.pNaviMesh = EngineFunction->Get_NaviMesh(L"NaviMesh_Zeds");
		TestGoreFast->Add_Component<Zed>(&GoreFast_Default);
		//////////////////////////////////////////////////////////////////////////


		++m_iZedCount;
	
}

void ZedManager::Generate_Scrake(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{
	
		GameObject* TestScrake = INSTANTIATE(OBJECT_TAG_ZED, L"Scrake" + to_wstring(m_iZedCount));
		TestScrake->Set_Position(_vPos);
		TestScrake->Set_Scale(Vector3(0.3f, 0.25f, 0.3f));
		//TestScrake->Set_Rotation(_qRot);

		TestScrake->Add_Component<StateController>();
		auto ZedStateCtrl = TestScrake->Get_Component<StateController>();
		ZedStateCtrl->Add_State<Zed_Idle>(L"Zed_Idle");
		ZedStateCtrl->Add_State<Zed_Walk>(L"Zed_Walk");
		ZedStateCtrl->Add_State<Zed_Run>(L"Zed_Run");
		ZedStateCtrl->Add_State<Zed_Att>(L"Zed_Att");
		ZedStateCtrl->Add_State<Zed_Hit>(L"Zed_Hit");
		ZedStateCtrl->Add_State<Zed_Death>(L"Zed_Death");
		ZedStateCtrl->Set_InitState(L"Zed_Idle");

		Mesh_Renderer::Desc Scrake_Mesh;
		Scrake_Mesh.szMeshName = L"Scrake";
		Scrake_Mesh.vRot = Vector3(0.f, 180.f, 0.f);
		TestScrake->Add_Component<Mesh_Renderer>(&Scrake_Mesh);

		AnimationController::Desc Scrake_Anim;
		Scrake_Anim.InitIndex = 0;
		Scrake_Anim.bLoop = true;
		Scrake_Anim.bClone = true;
		TestScrake->Add_Component<AnimationController>(&Scrake_Anim);

		SphereCollider::Desc Scrake_Col;
		Scrake_Col.fRadius = 12.5f;
		Scrake_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		Scrake_Col.szColName = L"Body";
		TestScrake->Add_Component<SphereCollider>(&Scrake_Col);

		Zed::Desc Scrake_Default;
		Scrake_Default.tZed_Status = arrZedInfo[ZED_Scrake];
		Scrake_Default.pNaviMesh = EngineFunction->Get_NaviMesh(L"NaviMesh_Zeds");
		TestScrake->Add_Component<Zed>(&Scrake_Default);

		++m_iZedCount;
	
}

void ZedManager::Generate_Patriarch(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{
	
		GameObject* TestPatriarch = INSTANTIATE(OBJECT_TAG_ZED, L"Patriarch" + to_wstring(m_iZedCount));
		TestPatriarch->Set_Position(_vPos);
		TestPatriarch->Set_Scale(Vector3(0.25f, 0.2f, 0.25f));
		//TestPatriarch->Set_Rotation(_qRot);

		TestPatriarch->Add_Component<StateController>();
		auto ZedStateCtrl = TestPatriarch->Get_Component<StateController>();
		//보스용 스테이터스 만들꺼임
		//ZedStateCtrl->Add_State<Zed_Idle>(L"Zed_Idle");
		//ZedStateCtrl->Add_State<Zed_Walk>(L"Zed_Walk");
		//ZedStateCtrl->Add_State<Zed_Run>(L"Zed_Run");
		//ZedStateCtrl->Add_State<Zed_Att>(L"Zed_Att");
		//ZedStateCtrl->Add_State<Zed_Hit>(L"Zed_Hit");
		//ZedStateCtrl->Add_State<Zed_Death>(L"Zed_Death");
		//ZedStateCtrl->Set_InitState(L"Zed_Idle");

		Mesh_Renderer::Desc Patriarch_Mesh;
		Patriarch_Mesh.szMeshName = L"Patriarch";
		Patriarch_Mesh.vRot = Vector3(0.f, 180.f, 0.f);
		TestPatriarch->Add_Component<Mesh_Renderer>(&Patriarch_Mesh);

		AnimationController::Desc Patriarch_Anim;
		Patriarch_Anim.InitIndex = 1;
		Patriarch_Anim.bLoop = true;
		Patriarch_Anim.bClone = true;
		TestPatriarch->Add_Component<AnimationController>(&Patriarch_Anim);

		SphereCollider::Desc Patriarch_Col;
		Patriarch_Col.fRadius = 12.5f;
		Patriarch_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		Patriarch_Col.szColName = L"Body";
		TestPatriarch->Add_Component<SphereCollider>(&Patriarch_Col);

		Zed::Desc Patriarch_Default;
		Patriarch_Default.tZed_Status = arrZedInfo[ZED_Patriarch];
		TestPatriarch->Add_Component<Zed>(&Patriarch_Default);

		++m_iZedCount;
	
}

void ZedManager::KillThemAll()
{
	for (auto& zed : EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_ZED))
	{
		zed->Set_Alive(false);
	}

	m_iZedCount = 0;
}

int ZedManager::Get_ZedCount()
{
	return m_iZedCount;
}

Vector3 ZedManager::Get_ZedGenLocate(eZedGenLocate _eZedGenLocate)
{
	return arrZedGenLocate[_eZedGenLocate];
}

Vector3 ZedManager::Get_ZedGenLocate(int _iZedGenLocate)
{
	return arrZedGenLocate[_iZedGenLocate];
}

void ZedManager::Set_ZedCount(int _Count)
{
	m_iZedCount = _Count;
}

void ZedManager::Add_ZedCount(int _Count)
{
	m_iZedCount += _Count;
}

