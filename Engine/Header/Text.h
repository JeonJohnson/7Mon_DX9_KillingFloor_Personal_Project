#pragma once

#ifndef _TEXT_H_
#define _TEXT_H_

#include "Engine_Include.h"

#include "UI_Component.h"

//https://m.blog.naver.com/PostView.nhn?blogId=power2845&logNo=50147975350&proxyReferer=https:%2F%2Fwww.google.com%2F
class DLL_STATE Text : public UI_Component
{
	
	friend class UI;

public:
	struct Desc
	{
		//D3DXFONT_DESC		
		//INT Height; => 높이 
		//UINT Width; => 너비 : 높이에 맞춰서 잘 나옴. 
				//=>가끔 안나오는 폰트는 가변형 글꼴임. 그런건 높이 /2 로 수정해주삼
			//인생꿀팁 
			//굴림 : 가변폭 글꼴
			//굴림체 : 고정폭 글꼴
		//UINT Weight; => 굵기 : Bold효과
		//UINT MipLevels; => defualt 1
		//BOOL Italic; => 기울임
		//BYTE CharSet; => 한글 쓸려면 HANGUL_CHARSET 해야함.
		//BYTE OutputPrecision; => Default
		//BYTE Quality; => Default
		//BYTE PitchAndFamily; => Defualt
		//WCHAR FaceName[LF_FACESIZE]; => 폰트 이름.

		//FW_DONTCARE	0
		//FW_THIN	100
		//FW_EXTRALIGHT	200
		//FW_ULTRALIGHT	200
		//FW_LIGHT	300
		//FW_NORMAL	400
		//FW_REGULAR	400
		//FW_MEDIUM	500
		//FW_SEMIBOLD	600
		//FW_DEMIBOLD	600
		//FW_BOLD	700
		//FW_EXTRABOLD	800
		//FW_ULTRABOLD	800
		//FW_HEAVY	900
		//FW_BLACK	900

		//Color => D3DXCOLOR_ARGB(0~255);
		//OPTION =>
			//DT_BOTTOM : 텍스트를 바닥에 정렬합니다.
				//->DT_SINGLELINE 플래그가 지정되어 있을 경우에만 사용할 수 있습니다.
			//DT_CALCRECT :  출력될 텍스트의 너비와 높이를 계산합니다.
				//->이 플래그가 지정되어 있을 경우 텍스트는 출력되지 않고 DrawText 함수는 높이를 리턴합니다.
			//DT_CENTER : 텍스트를 가운데 정렬합니다.
			//DT_LEFT : 텍스트를 왼쪽 정렬합니다.
			//DT_NOCLIP : 화면 밖을 벗어나는 텍스트도 출력합니다.
				//->이 플래그가 지정되었을 경우 DrawText 함수는 약간 더 빨라집니다.
			//DT_RIGHT : 텍스트를 오른쪽 정렬합니다.
			//DT_SINGLELINE : 모든 텍스트를 한 줄로 출력합니다.
			//DT_TOP : 텍스트를 맨 위에 정렬합니다.
			//DT_VCENTER : 텍스트를 수직 가운데에 정렬합니다.
				//->DT_SINGLELINE : 플래그가 지정되어 있을 경우에만 사용할 수 있습니다.
			//DT_WORDBREAK : 텍스트가 사각 영역 끝을 넘을 경우 자동개행합니다.
				//->이 플래그가 지정되지 않을 경우 모든 텍스트는 한 줄로 출력됩니다.
		//LPDIRECT3DDEVICE9		Dx9Device;

		int iHeight = 12;
		int	iWidth = 0;
		UINT	iWeight = FW_HEAVY;
		bool bItalic = false;
		bool bHanGul = true;
		wstring szFontName = L"Default";
		//짤막상식
		
		wstring	szScript;

		D3DXCOLOR tColor = D3DCOLOR_ARGB(255, 255, 255, 255);

		DWORD	ulOption = DT_NOCLIP | DT_CENTER | DT_VCENTER;

		Vector2 vOffSet = { 0.f,0.f };
		RECT	tRenderRect = { 0,0,1280,720 };
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

public: /* Get */
	virtual UI_KIND Get_UIkind() const override;
	wstring		Get_Script();

public: /* Set */
	void		Set_RenderRect(const RECT& _rect);
	void		Set_Script(const wstring& _script);
	void		Add_Script(const wstring& _script);
	void		Set_Color(const D3DXCOLOR& _color);

private:
	LPDIRECT3DDEVICE9		m_pDX9_Device = nullptr;
	LPD3DXSPRITE			m_pDX9_Sprite = nullptr;

	LPD3DXFONT				m_pDx9_Font = nullptr;
	
private:
	UI_KIND					m_eUiKind = UI_KIND::UI_TEXT;

	RECT					m_tRect;
	Vector2					m_vOffSet;

	wstring					m_szScript;
	DWORD					m_Option;
	D3DXCOLOR				m_Color;

	D3DXFONT_DESCW			m_tFontDesc;

	

	

	//INT Height; => 높이 
	//UINT Width; => 너비 : 높이에 맞춰서 잘 나옴. 가끔 안나오는 폰트는 높이 /2 로 수정해주삼
	//UINT Weight; => 굵기 : Bold효과
	//UINT MipLevels; => defualt 1
	//BOOL Italic; => 기울임
	//BYTE CharSet; => 한글 쓸려면 HANHUL_CHARSET 해야함.
	//BYTE OutputPrecision; => Default
	//BYTE Quality; => Default
	//BYTE PitchAndFamily; => Defualt
	//WCHAR FaceName[LF_FACESIZE]; => 폰트 이름.
};


#endif // _TEXT_H_