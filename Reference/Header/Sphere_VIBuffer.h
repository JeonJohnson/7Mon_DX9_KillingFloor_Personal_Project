#pragma once

#ifndef _SPHERE_VIBUFFER_H_
#define _SPHERE_VIBUFFER_H_

#include "Engine_Include.h"

#include "VIBuffer.h"

class Sphere_VIBuffer : public VIBuffer
{
	
public:
	Sphere_VIBuffer();
	virtual ~Sphere_VIBuffer();

public:
	virtual void Initialize() override;

public:
	virtual HRESULT Create_VBuffer() override;
	virtual HRESULT Create_IBuffer() override;

private:
	int		m_iHeightSliceCount;
	int		m_iWidthSliceCount;
	float	m_fRadius;
};

#endif // _SPHERE_VIBUFFER_H_