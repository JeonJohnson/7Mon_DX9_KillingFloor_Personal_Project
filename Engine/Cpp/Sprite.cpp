#include "..\Header\Sprite.h"

#include "Ui.h"

#include "DeviceManager.h"
#include "ResourceManager.h"

Sprite::Sprite(Desc * _desc)
{
	m_pDX9_Sprite = DeviceManager::Get_Instance()->Get_DX9_Sprite();
	assert(L"Sprite Com Load Failed to Sprite" && m_pDX9_Sprite);
	
	//Texture불러오기.
	m_pTexture = ResourceManager::Get_Instance()->Get_Resource<Texture>(_desc->TextureName);
	m_iTextureNum = _desc->iTextureNum;
}

Sprite::~Sprite() 
{
}

void Sprite::Initialize()
{
	//렉트지정
}

void Sprite::Update()
{
}

void Sprite::LateUpdate()
{
}

void Sprite::ReadyRender()
{
}

void Sprite::Render()
{
	if (m_pDX9_Sprite)
	{
		IDirect3DBaseTexture9*	TextureTemp = m_pTexture->Get_Texture(m_iTextureNum);
		D3DXIMAGE_INFO*			TextureInfo = m_pTexture->Get_TextureInfo(m_iTextureNum);

		Matrix matWorld, matScale, matTrans, matRot;

		D3DXMatrixScaling(&matScale,
			m_UiObject->Get_Scale().x,
			m_UiObject->Get_Scale().y,
			m_UiObject->Get_Scale().z);

		D3DXMatrixTranslation(&matTrans,
			m_UiObject->Get_Position().x,
			m_UiObject->Get_Position().y,
			0.1f);

		matWorld = matScale *matTrans;

		m_pDX9_Sprite->SetTransform(&matWorld);
		
		Vector3 vCenter = m_UiObject->Get_Center();

		if (FAILED(m_pDX9_Sprite->Draw(
			(LPDIRECT3DTEXTURE9)TextureTemp,
			nullptr,
			/*&m_UiObject->Get_Center(),*/
			&vCenter,
			nullptr, 
			D3DCOLOR_ARGB(255, 255, 255, 255))))
		{
			//Z값이 1되면 옵젝들보다 뒤에 있음.
			//0이면 폰트보다 앞에있어서 0.1로 해놨음.

			assert(0 && L"sprite drawing is failed");
		}
	}
}

void Sprite::Release()
{
}

UI_KIND Sprite::Get_UIkind() const
{
	return m_eUiKind;
}

IDirect3DBaseTexture9 * Sprite::Get_Texture(int _iNum)
{
	return m_pTexture->Get_Texture(_iNum);
}

D3DXIMAGE_INFO * Sprite::Get_TextureInfo(int _iNum)
{
	return m_pTexture->Get_TextureInfo(_iNum);
}

int Sprite::Get_TextureNum() const
{
	return m_iTextureNum;
}


