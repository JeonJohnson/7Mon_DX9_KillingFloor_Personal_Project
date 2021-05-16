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
}

void ZedManager::Update()
{
	HudManager::Get_Instance()->Set_TextZedCount(m_iZedCount);
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

void ZedManager::Generate_Clot(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{

		GameObject* TestClot = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" + to_wstring(m_iZedCount));
		TestClot->Set_Position(_vPos);
		TestClot->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));
		TestClot->Set_Rotation(_qRot);

		TestClot->Add_Component<StateController>();
		auto ZedStateCtrl = TestClot->Get_Component<StateController>();
		ZedStateCtrl->Add_State<Zed_Idle>(L"Zed_Idle");
		ZedStateCtrl->Add_State<Zed_Walk>(L"Zed_Fire");
		ZedStateCtrl->Add_State<Zed_Run>(L"Zed_Run");
		ZedStateCtrl->Add_State<Zed_Att>(L"Zed_Att");
		ZedStateCtrl->Add_State<Zed_Hit>(L"Zed_Hit");
		ZedStateCtrl->Add_State<Zed_Death>(L"Zed_Death");
		ZedStateCtrl->Set_InitState(L"Zed_Idle");

		Mesh_Renderer::Desc Clot_Test;
		Clot_Test.szMeshName = L"Clot";
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
		TestClot->Add_Component<Zed>(&Clot_Default);

		++m_iZedCount;

}

void ZedManager::Generate_GoreFast(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{
	
		GameObject* TestGoreFast = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" + to_wstring(m_iZedCount));
		TestGoreFast->Set_Position(_vPos);
		TestGoreFast->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));
		TestGoreFast->Set_Rotation(_qRot);

		Mesh_Renderer::Desc GoreFast_Mesh;
		GoreFast_Mesh.szMeshName = L"GoreFast";
		TestGoreFast->Add_Component<Mesh_Renderer>(&GoreFast_Mesh);

		AnimationController::Desc GoreFast_Anim;
		GoreFast_Anim.InitIndex = 0;
		GoreFast_Anim.bLoop = true;
		GoreFast_Anim.bClone = true;
		TestGoreFast->Add_Component<AnimationController>(&GoreFast_Anim);

		SphereCollider::Desc GoreFast_Col;
		GoreFast_Col.fRadius = 12.5f;
		GoreFast_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		GoreFast_Col.szColName = L"GoreFast_Body";
		TestGoreFast->Add_Component<SphereCollider>(&GoreFast_Col);


		//////////////////////////////////////////////////////////////////////////


		++m_iZedCount;
	
}

void ZedManager::Generate_Scrake(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{
	
		GameObject* TestScrake = INSTANTIATE(OBJECT_TAG_ZED, L"Scrake" + to_wstring(m_iZedCount));
		TestScrake->Set_Position(_vPos);
		TestScrake->Set_Scale(Vector3(0.3f, 0.2f, 0.3f));
		TestScrake->Set_Rotation(_qRot);

		Mesh_Renderer::Desc Scrake_Mesh;
		Scrake_Mesh.szMeshName = L"Scrake";
		TestScrake->Add_Component<Mesh_Renderer>(&Scrake_Mesh);

		AnimationController::Desc Scrake_Anim;
		Scrake_Anim.InitIndex = 0;
		Scrake_Anim.bLoop = true;
		Scrake_Anim.bClone = true;
		TestScrake->Add_Component<AnimationController>(&Scrake_Anim);

		SphereCollider::Desc Scrake_Col;
		Scrake_Col.fRadius = 12.5f;
		Scrake_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		Scrake_Col.szColName = L"Scrake_Body";
		TestScrake->Add_Component<SphereCollider>(&Scrake_Col);

		++m_iZedCount;
	
}

void ZedManager::Generate_Patriarch(const Vector3 & _vPos, const Quaternion & _qRot, ZED_INFO _tStatus)
{
	
		GameObject* TestPatriarch = INSTANTIATE(OBJECT_TAG_ZED, L"Clot" + to_wstring(m_iZedCount));
		TestPatriarch->Set_Position(_vPos);
		TestPatriarch->Set_Scale(Vector3(0.3f, 0.3f, 0.3f));
		TestPatriarch->Set_Rotation(_qRot);

		Mesh_Renderer::Desc Patriarch_Test;
		Patriarch_Test.szMeshName = L"Clot";
		TestPatriarch->Add_Component<Mesh_Renderer>(&Patriarch_Test);

		AnimationController::Desc Patriarch_Anim;
		Patriarch_Anim.InitIndex = 0;
		Patriarch_Anim.bLoop = true;
		Patriarch_Anim.bClone = true;
		TestPatriarch->Add_Component<AnimationController>(&Patriarch_Anim);

		SphereCollider::Desc Patriarch_Col;
		Patriarch_Col.fRadius = 12.5f;
		Patriarch_Col.vOffset = Vector3(0.f, 15.f, 0.f);
		Patriarch_Col.szColName = L"Clot_Body";
		TestPatriarch->Add_Component<SphereCollider>(&Patriarch_Col);

		++m_iZedCount;
	
}

