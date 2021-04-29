#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine_Include.h"

#include "Component.h"

class DLL_STATE Shader : public Component
{
public:
	struct Desc
	{
		wstring pFilePath = L"";
	};

public:
	explicit Shader(Desc* _desc);
	virtual ~Shader();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Release() override;

public:
	HRESULT					Ready_Shader(const wstring& _szShaderFilePath);

public: /* Get */
	LPD3DXEFFECT			Get_ComEffect() const;

public: /* Set */

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	LPD3DXEFFECT			m_pEffect = nullptr; //쉐이더용 컴객체
	LPD3DXBUFFER			m_pErrMsg = nullptr; //쉐이더 에러메시지 받아올 메모리

};

#endif //_SHADER_H_