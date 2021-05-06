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

	m_tColor = _desc->tColor;
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
		//사이즈 지 좃대로 나오던 이유
		//파일 불러올때 FromFileEx로 안하고 FromFile로 해서 그럼.

		IDirect3DBaseTexture9*	TextureTemp = m_pTexture->Get_Texture(m_iTextureNum);
		D3DXIMAGE_INFO*			TextureInfo = m_pTexture->Get_TextureInfo(m_iTextureNum);

		Matrix matWorld, matScale, matTrans, matRot;

		Vector3 scale = m_UiObject->Get_Scale();
		Vector3 pos = m_UiObject->Get_Position();

		D3DXMatrixScaling(&matScale,
			m_UiObject->Get_Scale().x,
			m_UiObject->Get_Scale().y,
			m_UiObject->Get_Scale().z);

		D3DXMatrixTranslation(&matTrans,
			m_UiObject->Get_Position().x,
			m_UiObject->Get_Position().y,
			0.1f);

		matWorld = matScale * matTrans;

		m_pDX9_Sprite->SetTransform(&matWorld);
		
		Vector3 vCenter = m_UiObject->Get_Center();

		if (FAILED(m_pDX9_Sprite->Draw(
			(LPDIRECT3DTEXTURE9)TextureTemp,
			nullptr,
			/*&m_UiObject->Get_Center(),*/
			&vCenter,
			nullptr, 
			m_tColor)))
		{
			//Z값이 1되면 옵젝들보다 뒤에 있음.
			//0이면 폰트보다 앞에있어서 0.1로 해놨음.

			assert(0 && L"sprite drawing is failed");
		}
	}
}

void Sprite::Release()
{
	//Texture관련된거는 ResourceManager에서 지워줄꺼다. 이거야.
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

float Sprite::Get_Alpha()
{
	return m_tColor.a;
}

void Sprite::Set_Alpha(float _fAlpha)
{
	m_tColor.a = _fAlpha;
}

void Sprite::Add_Alpha(float _fAlpha)
{//줄일 수록 투명해짐.
	//ㅋㅋㅋㅋ 여기는 D3DCOLOR_RGBA값 아님...
	// 0~1사이 값임!
	float fTemp = m_tColor.a;

	fTemp += _fAlpha;

	if (fTemp <= 0.f)
	{
		fTemp = 0.f;
	}

	if (fTemp >= 1.f)
	{
		fTemp = 1.f;
	}

	m_tColor.a = fTemp;
}


