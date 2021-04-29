#pragma once

#ifndef _VIBUFFER_H_
#define _VIBUFFER_H_

#include "Engine_Include.h"

#include "CResource.h"

class DLL_STATE VIBuffer : public CResource
{
//��� Ŭ������ ��ӹް�
	//VIBuffer Objs (Tri, Rect, Cube ��)����
	//������ ������ ������ ���� �θ� Ŭ����.
	//Create ���ִ°� �� ���� ���ε�
	//Render�� VIBufferRenderer����.
	//VIBufferRenderer���� �� �������� ������ �ҷ��´�. �̰ž�.

	/* �ش�Ƽ mk1 ��� 
	0. �갡 ���ҽ� ��� ����.
	1. VIBuffer������ 
		LPDirectVertexbuffer/IndexBuffer ������
		���ؽ� ���� ������ ����������.
	2. �긦 ��ӹ޴� �� �ɢhƮ�鿡�� CreateVertexBuffer/CreateIndexBuffer��.

	3. client���� gameObject���� VIBufferRenderer į������Ʈ �߰�.
	4. VIBufferRenderer�� IRenderer ��ӹ���. => �˾Ƽ� PreRedner ��Ʈ����
		RenderManager�� �Ѱ��༭ ���.
	5. VIBufferRenderer į����Ʈ Desc���� ���ϴ� ����� wstring �־��ָ�
	6. �� desc�� �� ��� ResourceManager���� �˸��� VIBuffer�� ã�Ƽ� ������.
		(���ø�����)
	7. ������ �� VIBuffer obj�� ���� Create���ְ� �츮�� Render�� ���ָ� �ȴ�. �̰ž�.
	*/

	//=> first of all, �� �� ���ҽ��Ŵ��� �ϴ� ������
		//VIBufferRenderer���� �� ������
		//��� �ٷ� �ش�Ǵ� VIBufferģ�� ã�Ƽ�	
		// ����ϱ�.
		//���߿� �ؽ��� ������ ���ҽ��Ŵ��� ����

	/* �½� �����ӿ�ũ ���
	1. ViBuffer�� ������ ��� ���� �Ӹ� �ƴ϶� ���� Create���� ����.
	2. 
	*/
public:
	VIBuffer();
	virtual ~VIBuffer();

public:
	virtual void Initialize() = 0;
	virtual void Release();

public:
	virtual HRESULT Create_VBuffer() = 0;
	virtual HRESULT Create_IBuffer() = 0;
	//virtual void	VI_Setting() = 0;
public:
	/* Get */
	const wstring&			Get_Name() const;

	LPDIRECT3DVERTEXBUFFER9	Get_VBuffer_Com()	const;
	const VBUFFER_INFO&		Get_VBuffer_Info()	const;

	LPDIRECT3DINDEXBUFFER9	Get_IBuffer_Com()	const;
	const IBUFFER_INFO&		Get_IBuffer_Info()	const;
	D3DPRIMITIVETYPE		Get_DrawType()		const;
	int						Get_RenderLayer()	const;
	
	VIBUFFER_KIND			Get_Kind()			const;
public:
	/* Set */
	void		Set_Name(const wstring& _name);
	
	void		Set_VBufferInfo(const VBUFFER_INFO& _tVBuffer);
	void		Set_IBufferInfo(const IBUFFER_INFO& _tIBuffer);
	void		Set_DrawType(D3DPRIMITIVETYPE _type);
	void		Set_RenderLayer(int _iRenderLayer);


	virtual void	Set_Texture(class Texture* _pTexture);
	virtual HRESULT Render_Texture(int _iNum);
	virtual HRESULT Render_Texture(LPD3DXEFFECT _pEffect, const char* _ShaderTexName, int _iTexNum);

protected:
	VIBUFFER_KIND			m_eKind;

	//LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;
	wstring					m_wName = L"";

	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	VBUFFER_INFO			m_tVBInfo;

	LPDIRECT3DINDEXBUFFER9	m_pIB = nullptr;
	IBUFFER_INFO			m_tIBInfo;

	D3DPRIMITIVETYPE		m_eDrawType = D3DPT_TRIANGLELIST;

	int		m_iRenderLayer = 0;
	
	
};

#endif //_VIBUFFER_H_

