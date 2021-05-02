#pragma once

#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include "Engine_Include.h"

#include "Light.h"

class LightManager
{
	Declare_Singleton(LightManager)

public:
	LightManager();
	virtual ~LightManager();

public:
	void Initialize();
	void Release();

public: /* Get */
	Light*			Get_LightByName(const wstring& _Name);
	

public: /* Set */
	void			Insert_Light(D3DLIGHT9* _pLight, const wstring& _Name);


public:


private:
	unordered_map<wstring, Light*> m_umLightList;

};

#endif //_LIGHT_MANAGER_H_
