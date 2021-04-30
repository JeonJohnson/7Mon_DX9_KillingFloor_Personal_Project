#pragma once

#ifndef _FUNCTION_STRING_H_
#define _FUNCTION_STRING_H_

#include "Engine_Include.h"

class Function_String
{
public:
	Function_String();
	~Function_String();

public: /* to wstring */
	static wstring stringTowstring(const string& _str, wstring _wstr)
	{
		_wstr.assign(_str.begin(), _str.end());
	}

	static const wstring& TCHAR2wstring(const TCHAR * _tchar)
	{
		wstring temp = (wchar_t*)_tchar;
		return temp;
	}

	static const TCHAR*	wstring2TCHAR(const wstring& _wstring)
	{
		TCHAR temp[255];
		wcscpy_s(temp, _wstring.c_str());
		return temp;
	}
public:

public:

private:


};

#endif //_FUNCTION_STRING_H_