#pragma once

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Engine_Include.h"

class DLL_STATE Light 
{

	friend class LightManager;

public:
	Light();
	virtual ~Light();

public:
	void			Initialize();
	void			Release();

public:
	HRESULT			Light_On();
	HRESULT			Light_Off();

public: /* Get */
	bool			Get_IsOn();
	D3DLIGHT9		Get_Light();

public: /* Set */
	void			Set_Light(D3DLIGHT9* _pLight);

public:
	
private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;
	
	bool					m_bOnOff = false;

	D3DLIGHT9				m_tDx9_Light;
	//D3DLIGHTTYPE    Type;            /* Type of light source */
	//D3DCOLORVALUE   Diffuse;         /* Diffuse color of light */
	//D3DCOLORVALUE   Specular;        /* Specular color of light */
	//D3DCOLORVALUE   Ambient;         /* Ambient color of light */
	//D3DVECTOR       Position;         /* Position in world space */
	//D3DVECTOR       Direction;        /* Direction in world space */
	//float           Range;            /* Cutoff range */
	//float           Falloff;          /* Falloff */
	//float           Attenuation0;     /* Constant attenuation */
	//float           Attenuation1;     /* Linear attenuation */
	//float           Attenuation2;     /* Quadratic attenuation */
	//float           Theta;            /* Inner angle of spotlight cone */
	//float           Phi;              /* Outer angle of spotlight cone */

};

#endif //_LIGHT_H_