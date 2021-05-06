#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_


#include "Engine_Include.h"

#include "UI_Component.h"

#include "Texture.h"


class DLL_STATE Sprite :public UI_Component
{
	friend class UI;

public:
	struct Desc 
	{		
		wstring		TextureName = L"";
		int			iTextureNum = 0;
		D3DXCOLOR	tColor = D3DCOLOR_RGBA(255, 255, 255, 255);

	};
public:
	Sprite(Desc* _desc);
	virtual ~Sprite();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Render() override;
	virtual void Release() override;

public: /* function */

public: /* Get */
	virtual UI_KIND Get_UIkind() const override;

	IDirect3DBaseTexture9*			Get_Texture(int _iNum = 0);
	D3DXIMAGE_INFO*					Get_TextureInfo(int _iNum = 0);
	
	int				Get_TextureNum() const;


	float			Get_Alpha();

public: /* Set */
	void			Set_Alpha(float _fAlpha);
	void			Add_Alpha(float _fAlpha);

private:
	UI_KIND				m_eUiKind = UI_KIND::UI_SPRITE;

	LPD3DXSPRITE		m_pDX9_Sprite = nullptr;
	Texture*			m_pTexture = nullptr;
	int					m_iTextureNum = 0;

	float				m_fWidth;
	float				m_fHeight;
	RECT				m_tRect;
	D3DXCOLOR			m_tColor;

};

#endif //_SPRITE_H_