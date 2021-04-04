#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Engine_Include.h"

#include "CResource.h"
class Texture : public CResource
{
public:
	Texture();
	virtual ~Texture();
	
public:
	virtual void Initialize() override;
	virtual void Release() override;

public: /* Function */

public: /* Get */
	vector<IDirect3DBaseTexture9*>	Get_Textures();
	IDirect3DBaseTexture9*			Get_Texture(int _iNum);
	
public: /* Set */
	HRESULT Insert_Texture(const wstring& _szPath);


private:
	LPDIRECT3DDEVICE9					m_pDX9_Device = nullptr;
	vector<IDirect3DBaseTexture9*>		m_vecTextures;

};

#endif //_TEXTURE_H_