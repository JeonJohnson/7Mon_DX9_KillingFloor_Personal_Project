#pragma once

#ifndef _FUNCTION_MATH_H_
#define _FUNCTION_MATH_H_

#include "Engine_Include.h"

class DLL_STATE Function_Math
{
public:
	Function_Math();
	~Function_Math();

	float	static RandFloat(float _fMin, float _fMax)
	{
		float randFloat = (((rand() % 10) + 1) / 10.f);
		int temp = (int)(_fMax - _fMin);
		int temp2 = rand() & temp;
		

		randFloat += _fMin + temp2;

		if (randFloat > _fMax)
		{
			randFloat = _fMax;
		}

		return randFloat;
	}

	
};

#endif //_FUNCTION_MATH_H_