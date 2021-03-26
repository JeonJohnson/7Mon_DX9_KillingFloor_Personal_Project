#pragma once

#ifndef _VIBUFFER_H_
#define _VIBUFFER_H_

#include "Engine_Include.h"

class VIBuffer
{
//��� Ŭ������ ��ӹް�
	//VIBuffer Objs (Tri, Rect, Cube ��)����
	//������ ������ ������ ���� �θ� Ŭ����.

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
	void Initialize();
	void Release();

public:

public:

private:
	LPDIRECT3DDEVICE9	m_pDX9Device = nullptr;
	wstring				m_wName = L"";



};

#endif

