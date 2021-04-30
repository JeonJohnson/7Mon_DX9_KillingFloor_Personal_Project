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


	};
public:
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

public:

public:

private:
	Save_TerrainLayOut*		m_pTerrainSave = nullptr;
};

#endif //_SAVE_INFO_H_