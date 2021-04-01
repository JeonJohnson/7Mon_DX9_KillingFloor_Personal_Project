#pragma once

#ifndef _SKYBOX_VIBUFFER_DDS_H_
#define _SKYBOX_VIBUFFER_DDS_H_

#include "Engine_Include.h"

#include "VIBuffer.h"

class SkyBox_VIBuffer_DDS :
	public VIBuffer
{
public:
	SkyBox_VIBuffer_DDS();
	virtual ~SkyBox_VIBuffer_DDS();

public:
	virtual void Initialize() override;

public:
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;
};

#endif //_SKYBOX_VIBUFFER_DDS_H_