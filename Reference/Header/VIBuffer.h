#pragma once

#ifndef _VIBUFFER_H_
#define _VIBUFFER_H_

#include "Engine_Include.h"

class VIBuffer
{
//리쏘스 클래스를 상속받고
	//VIBuffer Objs (Tri, Rect, Cube 등)들이
	//가지고 있을거 가지고 있을 부모 클래스.

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
	void Initialize();
	void Release();

public:

public:

private:
	LPDIRECT3DDEVICE9	m_pDX9Device = nullptr;
	wstring				m_wName = L"";



};

#endif

