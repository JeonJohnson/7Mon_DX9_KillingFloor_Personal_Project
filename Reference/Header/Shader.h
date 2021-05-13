#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine_Include.h"

#include "CResource.h"

class DLL_STATE Shader : public CResource
{	
public:
	explicit Shader();
	 ~Shader();

public:
	virtual void Initialize() override;
	virtual void Release() override;

public:
	HRESULT					Insert_Shader(const wstring& _szShaderFilePath);

public: /* Get */
	LPD3DXEFFECT			Get_EffectCom() const;

public: /* Set */


private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	LPD3DXEFFECT			m_pEffect = nullptr; //쉐이더용 컴객체
	LPD3DXBUFFER			m_pErrMsg = nullptr; //쉐이더 에러메시지 받아올 메모리


										


};

#endif //_SHADER_H_