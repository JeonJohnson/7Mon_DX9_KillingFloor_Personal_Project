#pragma once

#ifndef _TRIANGLE_VIBUFFER_COLOR_H_
#define _TRIANGLE_VIBUFFER_COLOR_H_

#include "Engine_Include.h"

#include "VIBuffer.h"

class Triangle_VIBuffer_Color : public VIBuffer
{
public:
	Triangle_VIBuffer_Color();
	virtual ~Triangle_VIBuffer_Color();

public:
	virtual void Initialize() override;

public:
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT	Create_IBuffer() override;

public:


public:



private:
	
	
};

#endif //_TRIANGLE_VIBUFFER_COLOR_H_