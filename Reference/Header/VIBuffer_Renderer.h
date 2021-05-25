#pragma once

#ifndef _VIBUFFER_RENDERER_H_
#define _VIBUFFER_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"
#include "VIBuffer.h"
#include "Shader.h"

class DLL_STATE VIBuffer_Renderer : public Renderer
{
	//VIBuffer Objģ������ Component�� �����ؼ�
	//Desc�� �ް� �����ؼ� �˸��� VIBuffer�� �������� ������
	//RenderManager�� �Ѱ��� ģ��.
	//Renderer�� Component�� ��ӹް� ������ �ֵ� �� į������Ʈ��
public:
	struct Desc 
	{
		wstring		wBufferName = L"Tri_Color";
		wstring		wTextureName = L"Default";
		
		wstring		szShaderName = L"Debug_VIBuffer";

		int			iLayer = 1;

		bool		bEffect = false;
		bool		bFade = false;
		float		fFadeSpd = 1.f;
	};

public:
	VIBuffer_Renderer(Desc* _desc);
	virtual ~VIBuffer_Renderer();

public:
	// Renderer��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	//virtual void ReadyRender() override;
	//�Լ� �������̵� ������ ���� Rednerer ReadyRender�� �Ⱥҷ���������
	virtual void Render() override;
	virtual void Release() override;

public: /* functions */
	HRESULT				Binding_Stream_VIBuffer();
	
	HRESULT				Create_Shader(const wstring& _szShaderName);
	HRESULT				Setup_ShaderTable();


public: /* Get */
	VIBuffer*			Get_VIBuffer() const;
	int					Get_TextureCount();

public: /* Set */
	void				Set_VIBuffer(const wstring& _wBufferName);
	void				Set_Texture(Texture* _pTexture);
	void				Set_TextureIndex(int _iIndex);

private:
	VIBuffer*		m_pVIBuffer = nullptr;
	wstring			m_pTextureName;
	Shader*			m_pShaderCom = nullptr;
	LPD3DXEFFECT	m_pEffectCom = nullptr;
	bool			m_bEffect;

	float			m_fAlpha = 0.0f;
	bool			m_bFade = false;
	float			m_fFadeSpd = 0.f;

	int				m_iTextureIndex = 0;

};

#endif //_VIBUFFER_RENDERER_H_