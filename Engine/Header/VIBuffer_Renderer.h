#pragma once

#ifndef _VIBUFFER_RENDERER_H_
#define _VIBUFFER_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"
#include "VIBuffer.h"
#include "Shader.h"

class DLL_STATE VIBuffer_Renderer : public Renderer
{
	//VIBuffer Obj친구들을 Component로 생성해서
	//Desc로 받고 구분해서 알맞은 VIBuffer의 정보값을 가져와
	//RenderManager로 넘겨줄 친구.
	//Renderer가 Component를 상속받고 있으니 애도 걍 캄ㅡ포난트임
public:
	struct Desc 
	{
		wstring		wBufferName = L"Tri_Color";
		wstring		wTextureName = L"Default";
		
		wstring		szShaderName = L"Debug_VIBuffer";

		int			iLayer = 1;

		bool		bEffect = false;
	};

public:
	VIBuffer_Renderer(Desc* _desc);
	virtual ~VIBuffer_Renderer();

public:
	// Renderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	//virtual void ReadyRender() override;
	//함수 오버라이딩 때문에 ㅅㅂ Rednerer ReadyRender이 안불러와졌던거
	virtual void Render() override;
	virtual void Release() override;

public: /* functions */
	HRESULT				Binding_Stream_VIBuffer();
	
	HRESULT				Create_Shader(const wstring& _szShaderName);
	HRESULT				Setup_ShaderTable();


public: /* Get */
	VIBuffer*			Get_VIBuffer() const;

public: /* Set */
	void				Set_VIBuffer(const wstring& _wBufferName);

private:
	VIBuffer*		m_pVIBuffer = nullptr;
	Shader*			m_pShaderCom = nullptr;
	LPD3DXEFFECT	m_pEffectCom = nullptr;
	bool			m_bEffect;

};

#endif //_VIBUFFER_RENDERER_H_