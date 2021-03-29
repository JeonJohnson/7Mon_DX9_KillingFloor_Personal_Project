#pragma once

#ifndef _VIBUFFER_H_
#define _VIBUFFER_H_

#include "Engine_Include.h"

class DLL_STATE VIBuffer abstract
{
//리쏘스 클래스를 상속받고
	//VIBuffer Objs (Tri, Rect, Cube 등)들이
	//가지고 있을거 가지고 있을 부모 클래스.
	//Create 해주는건 각 도형 본인들
	//Render은 VIBufferRenderer에서.
	//VIBufferRenderer에서 각 도형들의 정보를 불러온다. 이거야.

	/* 준니티 mk1 방식 
	0. 얘가 리소스 상속 받음.
	1. VIBuffer에서는 
		LPDirectVertexbuffer/IndexBuffer 변수랑
		버텍스 개수 정도만 가지고있음.
	2. 얘를 상속받는 각 옵줵트들에서 CreateVertexBuffer/CreateIndexBuffer함.

	3. client에서 gameObject한테 VIBufferRenderer 캄ㅡ포난트 추가.
	4. VIBufferRenderer은 IRenderer 상속받음. => 알아서 PreRedner 파트에서
		RenderManager로 넘겨줘서 출력.
	5. VIBufferRenderer 캄포난트 Desc에서 원하는 모양의 wstring 넣어주면
	6. 그 desc의 값 대로 ResourceManager에서 알맞은 VIBuffer을 찾아서 돌려줌.
		(템플릿으로)
	7. 어차피 그 VIBuffer obj가 직접 Create해주고 우리는 Render만 해주면 된다. 이거야.
	*/

	//=> first of all, 난 걍 리소스매니저 일단 제끼고
		//VIBufferRenderer에서 값 넣으면
		//기냥 바로 해당되는 VIBuffer친구 찾아서	
		// 출력하기.
		//난중에 텍스쳐 넣을때 리소스매니저 ㄱㄱ

	/* 태쌤 프레임와크 방식
	1. ViBuffer가 변수를 들고 있을 뿐만 아니라 직접 Create까지 해줌.
	2. 
	*/
public:
	VIBuffer();
	virtual ~VIBuffer();

public:
	virtual void Initialize() = 0;
	void Release();

public:
	virtual HRESULT Create_VBuffer() = 0;
	virtual HRESULT Create_IBuffer() = 0;
	
public:
	/* Get */
	const wstring&			Get_Name() const;

	LPDIRECT3DVERTEXBUFFER9	Get_VBuffer_Com()	const;
	const VBUFFER_INFO&		Get_VBuffer_Info()	const;

	LPDIRECT3DINDEXBUFFER9	Get_IBuffer_Com()	const;
	const IBUFFER_INFO&		Get_IBuffer_Info()	const;

	int						Get_RenderLayer()	const;

public:
	/* Set */
	void		Set_Name(const wstring& _name);

	void		Set_VBufferInfo(const VBUFFER_INFO& _tVBuffer);
	void		Set_IBufferInfo(const IBUFFER_INFO& _tIBuffer);

	void		Set_RenderLayer(int _iRenderLayer);

protected:
	LPDIRECT3DDEVICE9		m_pDX9Device = nullptr;
	wstring					m_wName = L"";

	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	VBUFFER_INFO			m_tVBInfo;

	LPDIRECT3DINDEXBUFFER9	m_pIB = nullptr;
	IBUFFER_INFO			m_tIBInfo;

	int		m_iRenderLayer = 0;

};

#endif

