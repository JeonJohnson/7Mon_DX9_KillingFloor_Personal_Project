#pragma once

#ifndef _VIBUFFER_RENDERER_H_
#define _VIBUFFER_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

class _declspec(dllexport) VIBuffer_Renderer :
	public Renderer
{
public:
	VIBuffer_Renderer();
	~VIBuffer_Renderer();
};

#endif