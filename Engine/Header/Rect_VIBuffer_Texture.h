#pragma once

#ifndef _RECT_VIBUFFER_TEXTURE_H_
#define _RECT_VIBUFFER_TEXTURE_H_

#include "Engine_Include.h"

#include "VIBuffer.h"

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

private:

};

#endif //_RECT_VIBUFFER_TEXTURE_H_