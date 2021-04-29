#pragma once

#ifndef _RECT_VIBUFFER_TEXTURE_H_
#define _RECT_VIBUFFER_TEXTURE_H_

#include "Engine_Include.h"

#include "VIBuffer.h"
#include "Texture.h"

class Rect_VIBuffer_Texture : public VIBuffer
{
public:
	Rect_VIBuffer_Texture();
	virtual ~Rect_VIBuffer_Texture();

public:
	virtual void Initialize() override;

public:

	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;


	virtual void	Set_Texture(Texture* _pTexture) override;
	virtual HRESULT Render_Texture(int _iNum) override;
	virtual HRESULT Render_Texture(LPD3DXEFFECT _pEffect, const char* _ShaderTexName, int _iTexNum) override;
	//virtual HRESULT	Redner_Texture()

private:
	Texture*	m_pTexture = nullptr;
	///*Test*/
	//IDirect3DBaseTexture9* test = nullptr;
};

#endif //_RECT_VIBUFFER_TEXTURE_H_