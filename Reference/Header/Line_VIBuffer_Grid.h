#pragma once

#ifndef _LINE_VIBUFFER_GRID_H_
#define _LINE_VIBUFFER_GRID_H_

#include "Engine_Include.h"

#include "VIBuffer.h"

class Line_VIBuffer_Grid : public VIBuffer
{
public:
	Line_VIBuffer_Grid();
	virtual ~Line_VIBuffer_Grid();

public:
	virtual void Initialize() override;
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;
};

#endif _LINE_VIBUFFER_GRID_H_