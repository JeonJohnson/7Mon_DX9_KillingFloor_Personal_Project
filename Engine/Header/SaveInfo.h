#pragma once

#ifndef _SAVE_INFO_H_
#define _SAVE_INFO_H_

#include "Engine_Include.h"
#include "Component.h"

class DLL_STATE	SaveInfo : public Component
{
public:
	struct Desc
	{
		wstring		szMeshPath = L"";
		wstring		szObjName = L"";
		int			iRenderLayer = 0;

		//Save_TerrainLayout*		tSaveInfo = nullptr;

	};
	explicit	SaveInfo(Desc* _desc);
	virtual		~SaveInfo();

public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	void	SaveInfo_Setting();

public:
	Save_TerrainLayout		Get_TerrainSave() const;

public:


private:
	Save_TerrainLayout		m_pTerrainSave;
};

#endif //_SAVE_INFO_H_