#pragma once

#ifndef _CUBE_VIBUFFER_COLOR_H_
#define _CUBE_VIBUFFER_COLOR_H_

#include "VIBuffer.h"
class Cube_VIBuffer_Color : public VIBuffer
{
public:
	Cube_VIBuffer_Color();
	virtual ~Cube_VIBuffer_Color();

public:
	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize() override;

public:
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;

private:
};

#endif //_CUBE_VIBUFFER_COLOR_H_