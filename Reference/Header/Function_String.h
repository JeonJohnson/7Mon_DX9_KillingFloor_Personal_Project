#pragma once

#ifndef _FUNCTION_STRING_H_
#define _FUNCTION_STRING_H_

#include "Engine_Include.h"

class DLL_STATE Function_String
{
public:
	Function_String();
	~Function_String();

public: /* to wstring */
	static void stringTowstring(const string& _str, wstring _wstr)
	{
		_wstr.assign(_str.begin(), _str.end());
	}

	//static const wstring& TCHAR2wstring(const TCHAR * _tchar)
	//{
	//	wstring temp = (wchar_t*)_tchar;
	//	return temp;
	//}

	//static const TCHAR*	wstring2TCHAR(const wstring& _wstring)
	//{
	//	TCHAR temp[255];
	//	wcscpy_s(temp, _wstring.c_str());
	//	return temp;
	//}

	static void TCHAR2wstring(const TCHAR * _tcharIn, wstring& _wstrOut)
	{
		_wstrOut = (wchar_t*)_tcharIn;
	}

	static void	wstring2TCHAR(const wstring& _wstrIn, TCHAR* _tcharOut)
	{
			const TCHAR* pTemp = (wchar_t*)_wstrIn.c_str();
		TCHAR arrTemp[255];
		_tcscpy_s(arrTemp, pTemp);

		memcpy(_tcharOut, arrTemp, sizeof(arrTemp));
	}
public:

public:

private:


};

#endif //_FUNCTION_STRING_H_