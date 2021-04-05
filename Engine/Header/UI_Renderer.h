#pragma once

#ifndef _UI_RENDERER_H_
#define _UI_RENDERER_H_

#include "Engine_Include.h"

#include "Renderer.h"

#include "Text.h"
#include "Sprite.h"

class UI_Renderer :	public Renderer
{
public:
	struct Desc
	{
		wstring		wTextName = L"";
		wstring		wSpriteName = L"";

		int			iLayer = 0;
	};

public:
	UI_Renderer(Desc* _desc);
	virtual ~UI_Renderer();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public: /* function */

public: /* Get */

public: /* Set */
	void Set_TextScript(const wstring& _script);

private: 
	LPD3DXSPRITE		m_pDX9_Sprite = nullptr;

	Text*				m_pText = nullptr;
	Sprite*				m_pSprite = nullptr;

};

#endif //_UI_RENDERER_H_