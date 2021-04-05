#pragma once

#ifndef _TEXT_H_
#define _TEXT_H_

#include "Engine_Include.h"

#include "Component.h"

//https://m.blog.naver.com/PostView.nhn?blogId=power2845&logNo=50147975350&proxyReferer=https:%2F%2Fwww.google.com%2F
class DLL_STATE Text : public Component
{
public:
	struct Desc
	{
		//D3DXFONT_DESC		
		//INT Height; => ���� 
		//UINT Width; => �ʺ� : ���̿� ���缭 �� ����. ���� �ȳ����� ��Ʈ�� ���� /2 �� �������ֻ�
		//UINT Weight; => ���� : Boldȿ��
		//UINT MipLevels; => defualt 1
		//BOOL Italic; => �����
		//BYTE CharSet; => �ѱ� ������ HANGUL_CHARSET �ؾ���.
		//BYTE OutputPrecision; => Default
		//BYTE Quality; => Default
		//BYTE PitchAndFamily; => Defualt
		//WCHAR FaceName[LF_FACESIZE]; => ��Ʈ �̸�.

		//Color => D3DXCOLOR_ARGB(0~255);
		//OPTION =>
			//DT_BOTTOM : �ؽ�Ʈ�� �ٴڿ� �����մϴ�.
				//->DT_SINGLELINE �÷��װ� �����Ǿ� ���� ��쿡�� ����� �� �ֽ��ϴ�.
			//DT_CALCRECT :  ��µ� �ؽ�Ʈ�� �ʺ�� ���̸� ����մϴ�.
				//->�� �÷��װ� �����Ǿ� ���� ��� �ؽ�Ʈ�� ��µ��� �ʰ� DrawText �Լ��� ���̸� �����մϴ�.
			//DT_CENTER : �ؽ�Ʈ�� ��� �����մϴ�.
			//DT_LEFT : �ؽ�Ʈ�� ���� �����մϴ�.
			//DT_NOCLIP : ȭ�� ���� ����� �ؽ�Ʈ�� ����մϴ�.
				//->�� �÷��װ� �����Ǿ��� ��� DrawText �Լ��� �ణ �� �������ϴ�.
			//DT_RIGHT : �ؽ�Ʈ�� ������ �����մϴ�.
			//DT_SINGLELINE : ��� �ؽ�Ʈ�� �� �ٷ� ����մϴ�.
			//DT_TOP : �ؽ�Ʈ�� �� ���� �����մϴ�.
			//DT_VCENTER : �ؽ�Ʈ�� ���� ����� �����մϴ�.
				//->DT_SINGLELINE : �÷��װ� �����Ǿ� ���� ��쿡�� ����� �� �ֽ��ϴ�.
			//DT_WORDBREAK : �ؽ�Ʈ�� �簢 ���� ���� ���� ��� �ڵ������մϴ�.
				//->�� �÷��װ� �������� ���� ��� ��� �ؽ�Ʈ�� �� �ٷ� ��µ˴ϴ�.
		LPDIRECT3DDEVICE9		Dx9Device;

		int iHeight = 12;
		int	iWidth = 0;
		int	iWeight = 300;
		bool bItalic = false;
		bool bHanGul = true;
		wstring szFontName = L"default";
		
		wstring	szScript;
		D3DXCOLOR tColor = D3DCOLOR_ARGB(255, 255, 255, 255);

		DWORD	ulOption = DT_NOCLIP | DT_CENTER;

		RECT	tRenderRect = { 0,0,425,720 };
	};
public:
	Text(Desc* _desc);
	virtual ~Text();
	
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void ReadyRender() override;
	virtual void Render() override;
	virtual void Release() override;

public: /* Function */
	void		Render_Text();

public: /* Get */


public: /* Set */
	void		Set_RenderRect(const RECT& _rect);
	void		Set_Script(const wstring& _script);
	void		Set_Color(const D3DXCOLOR& _color);

public:

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;

	LPD3DXFONT				m_pDx9_Font = nullptr;
	
private:
	RECT					m_tRect;
	wstring					m_szScript;
	DWORD					m_Option;
	D3DXCOLOR				m_Color;

	D3DXFONT_DESC			m_tFontDesc;
	//INT Height; => ���� 
	//UINT Width; => �ʺ� : ���̿� ���缭 �� ����. ���� �ȳ����� ��Ʈ�� ���� /2 �� �������ֻ�
	//UINT Weight; => ���� : Boldȿ��
	//UINT MipLevels; => defualt 1
	//BOOL Italic; => �����
	//BYTE CharSet; => �ѱ� ������ HANHUL_CHARSET �ؾ���.
	//BYTE OutputPrecision; => Default
	//BYTE Quality; => Default
	//BYTE PitchAndFamily; => Defualt
	//WCHAR FaceName[LF_FACESIZE]; => ��Ʈ �̸�.
};


#endif // _TEXT_H_