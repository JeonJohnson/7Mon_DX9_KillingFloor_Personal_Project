#pragma once

#ifndef _CUBE_VIBUFFER_TEXTURE_H_
#define _CUBE_VIBUFFER_TEXTURE_H_

#include "VIBuffer.h"
#include "Texture.h"

class Cube_VIBuffer_Texture : public VIBuffer
{
public:
	Cube_VIBuffer_Texture();
	virtual ~Cube_VIBuffer_Texture();

public:
	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize() override;

public:
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;

	virtual void	Set_Texture(Texture* _pTexture) override;
	virtual HRESULT Render_Texture(int _iNum) override;

private:
	Texture*	m_pTexture = nullptr;
};

#endif //_CUBE_VIBUFFER_TEXTURE_H_