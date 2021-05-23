#include "stdafx.h"
#include "..\Header\WeaponManager.h"
#include "Weapon.h"
#include "GameObject.h"
#include "Weapon_Status.h"

WeaponManager* WeaponManager::m_pInstance = nullptr;

WeaponManager::WeaponManager(Desc * _desc)
{
}

WeaponManager::~WeaponManager()
{

	Release();

}

WeaponManager * WeaponManager::Get_Instance()
{
	if (m_pInstance == nullptr)
	{
		GameObject*	mgrObj = INSTANTIATE(OBJECT_TAG_DEFAULT,L"WeaponManager");
		mgrObj->Add_Component<WeaponManager>();
		m_pInstance = mgrObj->Get_NewComponent<WeaponManager>();

		//m_pInstance->SetDontDestory(true);
	}

	return m_pInstance;
}

void WeaponManager::Destroy_Instance()
{
	if (m_pInstance)
	{
		GameObject::Destory(m_pInstance->Get_GameObject());
	}
}

void WeaponManager::Initialize()
{

}

void WeaponManager::Update()
{
	
}

void WeaponManager::LateUpdate()
{
}

void WeaponManager::ReadyRender()
{
}

void WeaponManager::Release()
{
}

void WeaponManager::Nogada_Data()
{
	{
		GameObject*		AK_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"AK47");
		
		WEAPON_INFO	AK_INFO;
		AK_INFO.m_szName = L"AK47";
		AK_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
		AK_INFO.m_eType = WEAPON_TYPE::Weapon_Rifle;
		AK_INFO.m_iDmg = 40;
		AK_INFO.m_iBuck = 1;
		AK_INFO.m_bAuto = true;
		AK_INFO.m_iMaxBullet = 30;
		AK_INFO.m_iCurBullet = 30;
		AK_INFO.m_iMaxMagazine = 6;
		AK_INFO.m_iCurMagazine = 6;
		AK_INFO.m_fMaxRapid = 0.1f;
		AK_INFO.m_fCurRapid = 0.f;
		AK_INFO.m_fAccuracy = 0.9f;
		AK_INFO.m_fRecoilForce = 20.f;
		AK_INFO.m_iWeight = 6;
		AK_INFO.m_iPrice = 1500;
		AK_INFO.m_iMagazinePrice = 40;

		Weapon_Status::Desc AK_Desc;
		AK_Desc.tWeaponStatus = AK_INFO;
		AK_Obj->Add_Component<Weapon_Status>(&AK_Desc);

		Insert_Weapon(AK_INFO.m_szName, AK_Obj);
	}

	{
		GameObject*		ShotGun_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"ShotGun");
	
		WEAPON_INFO		ShotGun_INFO;
		ShotGun_INFO.m_szName = L"ShotGun";
		ShotGun_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
		ShotGun_INFO.m_eType = WEAPON_TYPE::Weapon_Shotgun;
		ShotGun_INFO.m_iDmg = 30;
		ShotGun_INFO.m_iBuck = 6;
		ShotGun_INFO.m_bAuto = false;
		ShotGun_INFO.m_iMaxBullet = 6;
		ShotGun_INFO.m_iCurBullet = 6;
		ShotGun_INFO.m_iMaxMagazine = 60;
		ShotGun_INFO.m_iCurMagazine = 60;
		ShotGun_INFO.m_fMaxRapid = 1.f;
		ShotGun_INFO.m_fCurRapid = 0.f;
		ShotGun_INFO.m_fAccuracy = 0.75f;
		ShotGun_INFO.m_fRecoilForce = 60.f;
		ShotGun_INFO.m_iWeight = 5;
		ShotGun_INFO.m_iPrice = 1000;
		ShotGun_INFO.m_iMagazinePrice = 30;

		Weapon_Status::Desc ShotGun_Desc;
		ShotGun_Desc.tWeaponStatus = ShotGun_INFO;
		ShotGun_Obj->Add_Component<Weapon_Status>(&ShotGun_Desc);

		Insert_Weapon(ShotGun_INFO.m_szName, ShotGun_Obj);
	}

	{
		GameObject* M99_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"M99");

		WEAPON_INFO		M99_INFO;
		M99_INFO.m_szName = L"M99";
		M99_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
		M99_INFO.m_eType = WEAPON_TYPE::Weapon_Sniper;
		M99_INFO.m_iDmg = 200;
		M99_INFO.m_iBuck = 1;
		M99_INFO.m_bAuto = false;
		M99_INFO.m_iMaxBullet = 1;
		M99_INFO.m_iCurBullet = 1;
		M99_INFO.m_iMaxMagazine = 20;
		M99_INFO.m_iCurMagazine = 20;
		M99_INFO.m_fMaxRapid = 2.f;
		M99_INFO.m_fCurRapid = 0.f;
		M99_INFO.m_fAccuracy = 1.f;
		M99_INFO.m_fRecoilForce = 80.f;
		M99_INFO.m_iWeight = 12;
		M99_INFO.m_iPrice = 2000;
		M99_INFO.m_iMagazinePrice = 50;

		Weapon_Status::Desc	M99_Desc;
		M99_Desc.tWeaponStatus = M99_INFO;
		M99_Obj->Add_Component<Weapon_Status>(&M99_Desc);

		Insert_Weapon(M99_INFO.m_szName, M99_Obj);
	}
	
	{
		GameObject*	Beretta_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"Beretta");

		WEAPON_INFO		Beretta_INFO;
		Beretta_INFO.m_szName = L"Beretta";
		Beretta_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Secondary;
		Beretta_INFO.m_eType = WEAPON_TYPE::Weapon_Pistol;
		Beretta_INFO.m_iDmg = 20;
		Beretta_INFO.m_iBuck = 1;
		Beretta_INFO.m_bAuto = false;
		Beretta_INFO.m_iMaxBullet = 15;
		Beretta_INFO.m_iCurBullet = 15;
		Beretta_INFO.m_iMaxMagazine = 3;
		Beretta_INFO.m_iCurMagazine = 3;
		Beretta_INFO.m_fMaxRapid = 0.2f;
		Beretta_INFO.m_fCurRapid = 0.f;
		Beretta_INFO.m_fAccuracy = 0.9f;
		Beretta_INFO.m_fRecoilForce = 15.f;
		Beretta_INFO.m_iWeight = 1;
		Beretta_INFO.m_iPrice = 0;
		Beretta_INFO.m_iMagazinePrice = 10;

		Weapon_Status::Desc Beretta_Desc;
		Beretta_Desc.tWeaponStatus = Beretta_INFO;
		Beretta_Obj->Add_Component<Weapon_Status>(&Beretta_Desc);

		Insert_Weapon(Beretta_INFO.m_szName, Beretta_Obj);
	}
	
	{
		GameObject* Revolver_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"Revolver");

		WEAPON_INFO Revolver_INFO;
		Revolver_INFO.m_szName = L"Revolver";
		Revolver_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Secondary;
		Revolver_INFO.m_eType = WEAPON_TYPE::Weapon_Pistol;
		Revolver_INFO.m_iDmg = 50;
		Revolver_INFO.m_iBuck = 1;
		Revolver_INFO.m_bAuto = false;
		Revolver_INFO.m_iMaxBullet = 6;
		Revolver_INFO.m_iCurBullet = 6;
		Revolver_INFO.m_iMaxMagazine = 5;
		Revolver_INFO.m_iCurMagazine = 5;
		Revolver_INFO.m_fMaxRapid = 0.4f;
		Revolver_INFO.m_fCurRapid = 0.f;
		Revolver_INFO.m_fAccuracy = 1.f;
		Revolver_INFO.m_fRecoilForce = 40.f;
		Revolver_INFO.m_iWeight = 3;
		Revolver_INFO.m_iPrice = 750;
		Revolver_INFO.m_iMagazinePrice = 50;

		Weapon_Status::Desc Revolver_Desc;
		Revolver_Desc.tWeaponStatus = Revolver_INFO;
		Revolver_Obj->Add_Component<Weapon_Status>(&Revolver_Desc);

		Insert_Weapon(Revolver_INFO.m_szName, Revolver_Obj);
	}

	{
		GameObject* Knife_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"Knife");
		
		WEAPON_INFO		Knife_INFO;
		Knife_INFO.m_szName = L"Knife";
		Knife_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Melee;
		Knife_INFO.m_eType = WEAPON_TYPE::Weapon_Knife;
		Knife_INFO.m_iDmg = 35;
		Knife_INFO.m_iBuck = 1;
		Knife_INFO.m_bAuto = false;
		Knife_INFO.m_iMaxBullet = 0;
		Knife_INFO.m_iCurBullet = 0;
		Knife_INFO.m_iMaxMagazine = 0;
		Knife_INFO.m_iCurMagazine = 0;
		Knife_INFO.m_fMaxRapid = 0.6f;
		Knife_INFO.m_fCurRapid = 0.f;
		Knife_INFO.m_fAccuracy = 1.f;
		Knife_INFO.m_fRecoilForce = 0.f;
		Knife_INFO.m_iWeight = 0;
		Knife_INFO.m_iPrice = 0;
		Knife_INFO.m_iMagazinePrice = 0;

		Weapon_Status::Desc Knife_Desc;
		Knife_Desc.tWeaponStatus = Knife_INFO;
		Knife_Obj->Add_Component<Weapon_Status>(&Knife_Desc);

		Insert_Weapon(Knife_INFO.m_szName, Knife_Obj);
	}

	{
		GameObject* Injector_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"Injector");

		WEAPON_INFO		Injector_INFO;
		Injector_INFO.m_szName = L"Injector";
		Injector_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Special;
		Injector_INFO.m_eType = WEAPON_TYPE::Weapon_Injector;
		Injector_INFO.m_iDmg = 50; //Heal Amount
		Injector_INFO.m_iMaxBullet = 100; //최대치
		Injector_INFO.m_iCurBullet = 100; //현재 수치
		Injector_INFO.m_fMaxRapid = 2.5f; //충전 시간.
		Injector_INFO.m_fCurRapid = 0.f;

		Weapon_Status::Desc Injector_Desc;
		Injector_Desc.tWeaponStatus = Injector_INFO;
		Injector_Obj->Add_Component<Weapon_Status>(&Injector_Desc);

		Insert_Weapon(Injector_INFO.m_szName, Injector_Obj);
	}

	{
		GameObject* Bomb_Obj = INSTANTIATE(OBJECT_TAG_WEAPON, L"Bomb");

		WEAPON_INFO		Bomb_INFO;
		Bomb_INFO.m_szName = L"Bomb";
		Bomb_INFO.m_ePriority = WEAPON_PRIORITY::Weapon_Special;
		Bomb_INFO.m_eType = WEAPON_TYPE::Weapon_Bomb;
		Bomb_INFO.m_iDmg = 500;
		Bomb_INFO.m_iMaxBullet = 5;
		Bomb_INFO.m_iCurBullet = 1;
		Bomb_INFO.m_iMagazinePrice = 10;

		Weapon_Status::Desc Bomb_Desc;
		Bomb_Desc.tWeaponStatus = Bomb_INFO;
		Bomb_Obj->Add_Component<Weapon_Status>(&Bomb_Desc);

		Insert_Weapon(Bomb_INFO.m_szName, Bomb_Obj);
	}
}

GameObject * WeaponManager::Get_ProtoWeapon(const wstring & _szWeaponName)
{
	auto iter_find = m_umPrototypeWeapons.find(_szWeaponName);

	if (iter_find == m_umPrototypeWeapons.end())
	{
		return nullptr;
	}

	return (*iter_find).second;
}

GameObject * WeaponManager::Get_CloneWeapon(const wstring & _szWeaponName)
{
	auto iter_find = m_umPrototypeWeapons.find(_szWeaponName);

	if (iter_find == m_umPrototypeWeapons.end())
	{
		return nullptr;
	}

	Weapon_Status* Find_Status = (*iter_find).second->Get_Component<Weapon_Status>();
	if (Find_Status == nullptr)
	{
		Find_Status = (*iter_find).second->Get_NewComponent<Weapon_Status>();
	}


	GameObject* CloneWeapon = INSTANTIATE(OBJECT_TAG_WEAPON, Find_Status->m_tWeaponInfo.m_szName);
	
	WEAPON_INFO tempInfo = Find_Status->m_tWeaponInfo;

	Weapon_Status::Desc	tempDesc;
	tempDesc.tWeaponStatus = tempInfo;
	CloneWeapon->Add_Component<Weapon_Status>(&tempDesc);

	return CloneWeapon;
}

void WeaponManager::Insert_Weapon(const wstring& _szName, GameObject * _pWeapon )
{
	m_umPrototypeWeapons.emplace(_szName, _pWeapon);
}



//void WeaponManager::Release()
//{
//
//	//클래스는 웬만하면 memcpy 하지마셈.
//	//가상함수 테이블이 복사될 경우도 있고
//	//클래스 내에서 동적할당된 친구가 있을 경우 그 친구는 그냥 그 주소 값이 사라져벌임.
//
//	for (auto& cloneWeapon : m_listCloneWeapons)
//	{
//		delete cloneWeapon;
//		//cloneWeapon = nullptr;
//	}
//
//	for (auto& protoWeapon : m_umALLWeapon)
//	{
//		delete protoWeapon.second;
//	}
//}

//Weapon * WeaponManager::Get_Weapon(const wstring & _szWeaponName)
//{
//	auto iter_find = m_umALLWeapon.find(_szWeaponName);
//
//	if (iter_find == m_umALLWeapon.end())
//	{
//		return nullptr;
//	}
//	
//	return (*iter_find).second;
//}

//Weapon * WeaponManager::Get_CloneWeapon(const wstring & _szWeaponName)
//{
//	auto iter_find = m_umALLWeapon.find(_szWeaponName);
//
//	if (iter_find == m_umALLWeapon.end())
//	{
//		return nullptr;
//	}
//
//	Weapon* CloneTemp = new Weapon;
//	
//	memcpy(CloneTemp, ((*iter_find).second), sizeof(Weapon));
//	//memcpy(&CloneTemp->m_szName, &(*iter_find).second->m_szName,
//	//	sizeof((*iter_find).second->m_szName));
//
//	
//	//CloneTemp->m_szName = (*iter_find).second->m_szName;
//
//	m_listCloneWeapons.emplace_back(CloneTemp);
//
//	return CloneTemp;
//}

//void WeaponManager::Load_WeaponData(const wstring & _szDataPath)
//{
//	ifstream	readFile;
//	readFile.open(_szDataPath.c_str());
//
//	if (readFile.is_open())
//	{
//		
//		while (!readFile.eof())
//		{
//			string str;
//			getline(readFile, str);	
//		}
//
//		readFile.close();
//	}
//}

//void WeaponManager::Insert_Weapon(Weapon * _pWeapon)
//{
//	//wstring szName = _pWeapon->m_szName;
//	wstring szName = L"Temp";
//	m_umALLWeapon.emplace(szName, _pWeapon);
//
//}

//void WeaponManager::Nogada_Data()
//{
//	Weapon* AK = new Weapon;
//	AK->m_szName = L"AK47";
//	AK->m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
//	AK->m_eType = WEAPON_TYPE::Weapon_Rifle;
//	AK->m_iDmg = 40;
//	AK->m_iBuck = 1;
//	AK->m_bAuto = true;
//	AK->m_iMaxBullet = 30;
//	AK->m_iCurBullet = 30;
//	AK->m_iMaxMagazine = 6;
//	AK->m_iCurMagazine = 6;
//	AK->m_fMaxRapid = 0.1f;
//	AK->m_fCurRapid = 0.f;
//	AK->m_fAccuracy = 1.f;
//	AK->m_fRecoilForce = 10.f;
//	AK->m_iWeight = 6;
//	AK->m_iPrice = 1500;
//	AK->m_iMagazinePrice = 40;
//	Insert_Weapon(AK);
//
//	Weapon* ShotGun = new Weapon;
//	ShotGun->m_szName = L"ShotGun";
//	ShotGun->m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
//	ShotGun->m_eType = WEAPON_TYPE::Weapon_Shotgun;
//	ShotGun->m_iDmg = 30;
//	ShotGun->m_iBuck = 6;
//	ShotGun->m_bAuto = false;
//	ShotGun->m_iMaxBullet = 6;
//	ShotGun->m_iCurBullet = 6;
//	ShotGun->m_iMaxMagazine = 60;
//	ShotGun->m_iCurMagazine = 60;
//	ShotGun->m_fMaxRapid = 1.f;
//	ShotGun->m_fCurRapid = 0.f;
//	ShotGun->m_fAccuracy = 1.f;
//	ShotGun->m_fRecoilForce = 10.f;
//	ShotGun->m_iWeight = 5;
//	ShotGun->m_iPrice = 1000;
//	ShotGun->m_iMagazinePrice = 30;
//	Insert_Weapon(ShotGun);
//
//	Weapon* M99 = new Weapon;
//	M99->m_szName = L"M99";
//	M99->m_ePriority = WEAPON_PRIORITY::Weapon_Primary;
//	M99->m_eType = WEAPON_TYPE::Weapon_Sniper;
//	M99->m_iDmg = 150;
//	M99->m_iBuck = 1;
//	M99->m_bAuto = false;
//	M99->m_iMaxBullet = 1;
//	M99->m_iCurBullet = 1;
//	M99->m_iMaxMagazine = 20;
//	M99->m_iCurMagazine = 20;
//	M99->m_fMaxRapid = 2.f;
//	M99->m_fCurRapid = 0.f;
//	M99->m_fAccuracy = 1.f;
//	M99->m_fRecoilForce = 10.f;
//	M99->m_iWeight = 12;
//	M99->m_iPrice = 2000;
//	M99->m_iMagazinePrice = 50;
//	Insert_Weapon(M99);
//
//	Weapon* Beretta = new Weapon;
//	Beretta->m_szName = L"Beretta";
//	Beretta->m_ePriority = WEAPON_PRIORITY::Weapon_Secondary;
//	Beretta->m_eType = WEAPON_TYPE::Weapon_Pistol;
//	Beretta->m_iDmg = 20;
//	Beretta->m_iBuck = 1;
//	Beretta->m_bAuto = false;
//	Beretta->m_iMaxBullet = 15;
//	Beretta->m_iCurBullet = 15;
//	Beretta->m_iMaxMagazine = 3;
//	Beretta->m_iCurMagazine = 3;
//	Beretta->m_fMaxRapid = 0.2f;
//	Beretta->m_fCurRapid = 0.f;
//	Beretta->m_fAccuracy = 1.f;
//	Beretta->m_fRecoilForce = 10.f;
//	Beretta->m_iWeight = 1;
//	Beretta->m_iPrice = 0;
//	Beretta->m_iMagazinePrice = 10;
//	Insert_Weapon(Beretta);
//
//
//	Weapon* Revolver = new Weapon;
//	Revolver->m_szName = L"Revolver";
//	Revolver->m_ePriority = WEAPON_PRIORITY::Weapon_Secondary;
//	Revolver->m_eType = WEAPON_TYPE::Weapon_Pistol;
//	Revolver->m_iDmg = 50;
//	Revolver->m_iBuck = 1;
//	Revolver->m_bAuto = false;
//	Revolver->m_iMaxBullet = 6;
//	Revolver->m_iCurBullet = 6;
//	Revolver->m_iMaxMagazine = 5;
//	Revolver->m_iCurMagazine = 5;
//	Revolver->m_fMaxRapid = 0.4f;
//	Revolver->m_fCurRapid = 0.f;
//	Revolver->m_fAccuracy = 1.f;
//	Revolver->m_fRecoilForce = 10.f;
//	Revolver->m_iWeight = 3;
//	Revolver->m_iPrice = 750;
//	Revolver->m_iMagazinePrice = 50;
//	Insert_Weapon(Revolver);
//
//	Weapon* Knife = new Weapon;
//	Knife->m_szName = L"Knife";
//	Knife->m_ePriority = WEAPON_PRIORITY::Weapon_Melee;
//	Knife->m_eType = WEAPON_TYPE::Weapon_Knife;
//	Knife->m_iDmg = 35;
//	Knife->m_iBuck = 1;
//	Knife->m_bAuto = false;
//	Knife->m_iMaxBullet = 0;
//	Knife->m_iCurBullet = 0;
//	Knife->m_iMaxMagazine = 0;
//	Knife->m_iCurMagazine = 0;
//	Knife->m_fMaxRapid = 0.6f;
//	Knife->m_fCurRapid = 0.f;
//	Knife->m_fAccuracy = 1.f;
//	Knife->m_fRecoilForce = 0.f;
//	Knife->m_iWeight = 0;
//	Knife->m_iPrice = 0;
//	Knife->m_iMagazinePrice = 0;
//	Insert_Weapon(Knife);
//
//}
