#include "..\Header\Text.h"

#include "DeviceManager.h"

Text::Text(Desc * _desc)
{
	//assert(L"Dx9Device is nullptr At TextFont" && _desc->Dx9Device);

	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

	ZeroMemory(&m_tFontDesc, sizeof(D3DXFONT_DESC));

	m_tFontDesc.Height = (UINT)_desc->iHeight;
	if (_desc->iWidth != 0)
	{
		m_tFontDesc.Width = _desc->iWidth;
	}
	m_tFontDesc.Weight = (UINT)_desc->iWeight;

	m_tFontDesc.Italic = (BOOL)_desc->bItalic;

	if (_desc->bHanGul)
	{
		m_tFontDesc.CharSet = HANGUL_CHARSET;
	}

	if (_desc->szFontName != L"Default")
	{
		lstrcpy(m_tFontDesc.FaceName, _desc->szFontName.c_str());
	}


	m_szScript = _desc->szScript;
	m_Color = _desc->tColor;
	m_Option = _desc->ulOption;

	m_tRect = _desc->tRenderRect;

	//Initialize();

	m_eUiKind = UI_KIND::UI_TEXT;
}

Text::~Text()
{

}

void Text::Initialize()
{
	

	if (FAILED(D3DXCreateFontIndirect(m_pDX9_Device, &m_tFontDesc, &m_pDx9_Font)))
	{
		MsgBox(L"Error", L"Create Font Failed At Text");
	}
}

void Text::Update()
{
}

void Text::LateUpdate()
{
}

void Text::ReadyRender()
{
}

void Text::Render()
{
	if (m_pDx9_Font)
	{
		m_pDx9_Font->DrawTextW(
			nullptr,
			m_szScript.c_str(),
			-1,
			&m_tRect,
			m_Option,
			m_Color);
	}
}

void Text::Release()
{
	if (m_pDx9_Font)
	{
		m_pDx9_Font->Release();
		m_pDx9_Font = nullptr;
	}
}


wstring Text::Get_Script()
{
	return m_szScript;
}

void Text::Set_RenderRect(const RECT & _rect)
{
	m_tRect = _rect;
}

void Text::Set_Script(const wstring & _script)
{
	m_szScript = _script;
}

void Text::Add_Script(const wstring & _script)
{
	m_szScript += _script;
}

void Text::Set_Color(const D3DXCOLOR & _color)
{
	m_Color = _color;
}

UI_KIND Text::Get_UIkind() const
{
	return m_eUiKind;
}

