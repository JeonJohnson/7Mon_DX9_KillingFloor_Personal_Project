#pragma once

#ifndef _RECT_VIBUFFER_COLOR_H_
#define _RECT_VIBUFFER_COLOR_H_

#include "Engine_Include.h"

#include "VIBuffer.h"

class Rect_VIBuffer_Color :
	public VIBuffer
{
public:
	Rect_VIBuffer_Color();
	virtual ~Rect_VIBuffer_Color();

public:
	virtual void Initialize() override;

public:

	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;

private:

};

#endif //_RECT_VIBUFFER_COLOR_H_