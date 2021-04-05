#pragma once

#ifndef _CUBE_VIBUFFER_DDS_H_
#define _CUBE_VIBUFFER_DDS_H_

#include "Engine_Include.h"

#include "VIBuffer.h"
#include "Texture.h"

class Cube_VIBuffer_DDS : public VIBuffer
{
public:
	Cube_VIBuffer_DDS();
	virtual ~Cube_VIBuffer_DDS();

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

#endif //_CUBE_VIBUFFER_DDS_H_