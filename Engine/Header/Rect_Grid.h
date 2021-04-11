#pragma once

#ifndef _RECT_GRID_H_
#define _RECT_GRID_H_

#include "Engine_Include.h"

#include "VIBuffer.h"


class Rect_Grid : public VIBuffer
{
public:
	Rect_Grid();
	virtual ~Rect_Grid();

public:
	virtual void Initialize() override;

public:
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;

public:

public:

public:

private:

};

#endif //_RECT_GRID_H_