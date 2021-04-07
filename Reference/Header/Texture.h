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
	//vector<IDirect3DBaseTexture9*>	Get_AllTexturePair();
	IDirect3DBaseTexture9*			Get_Texture(int _iNum = 0);
	D3DXIMAGE_INFO*					Get_TextureInfo(int _iNum = 0);
	
public: /* Set */
	HRESULT Insert_Texture(const wstring& _szPath,
		TEXTURE_KIND _kind = TEXTURE_KIND::Texture_Image);


private:
	LPDIRECT3DDEVICE9					m_pDX9_Device = nullptr;

	typedef pair<IDirect3DBaseTexture9*, D3DXIMAGE_INFO*> TEXTURE_PAIR;

	vector<TEXTURE_PAIR>				m_vecTexturePair;

	//vector<IDirect3DBaseTexture9*>		m_vecTextures;
	//vector<D3DXIMAGE_INFO*>				m_vecImageInfo;

};

#endif //_TEXTURE_H_