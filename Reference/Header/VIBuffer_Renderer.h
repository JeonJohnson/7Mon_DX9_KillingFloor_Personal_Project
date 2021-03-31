#pragma once

#ifndef _VIBUFFER_RENDERER_H_
#define _VIBUFFER_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"
#include "VIBuffer.h"

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
		int			iLayer = 0;
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
	HRESULT Binding_Stream_VIBuffer();
	

public: /* Get */
	VIBuffer*			Get_VIBuffer() const;

public: /* Set */
	void	Set_VIBuffer(const wstring& _wBufferName);



private:
	VIBuffer*		m_pVIBuffer = nullptr;

	/*Test*/
	Matrix m_matView;
	Matrix m_matProj;
};

#endif //_VIBUFFER_RENDERER_H_