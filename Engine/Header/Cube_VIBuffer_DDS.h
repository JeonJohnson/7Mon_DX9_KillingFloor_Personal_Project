#pragma once

#ifndef _CUBE_VIBUFFER_DDS_H_
#define _CUBE_VIBUFFER_DDS_H_

#include "VIBuffer.h"
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

private:
};

#endif //_CUBE_VIBUFFER_DDS_H_