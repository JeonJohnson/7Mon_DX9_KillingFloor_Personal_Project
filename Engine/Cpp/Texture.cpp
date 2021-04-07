#include "..\Header\Texture.h"
#include "DeviceManager.h"



Texture::Texture()
{
	Initialize();
}


Texture::~Texture()
{
}

void Texture::Initialize()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Device loading failed at Texture." && m_pDX9_Device);

}

void Texture::Release()
{
}

//vector<IDirect3DBaseTexture9*> Texture::Get_AllTexturePair()
//{
//	return m_vecTexturePair;
//}

IDirect3DBaseTexture9 * Texture::Get_Texture(int _iNum)
{
	size_t VecSize = m_vecTexturePair.size();

	if ((size_t)_iNum < VecSize)
	{
		return m_vecTexturePair[_iNum].first;
	}
	else { return nullptr; }
}

D3DXIMAGE_INFO * Texture::Get_TextureInfo(int _iNum)
{
	size_t VecSize = m_vecTexturePair.size();

	if ((size_t)_iNum < VecSize)
	{
		return m_vecTexturePair[_iNum].second;
	}
	else { return nullptr; }
}

HRESULT Texture::Insert_Texture(const wstring & _szPath, TEXTURE_KIND _kind)
{
	IDirect3DBaseTexture9*	TexTemp = nullptr;
	D3DXIMAGE_INFO* ImageInfoTemp = nullptr;


	//TCHAR szFullPath[128] = L"../../Resource/Test/boss.png";

	if (_kind == TEXTURE_KIND::Texture_DDS)
	{
		//DDS ���� �ҷ��ö�
		if (FAILED(D3DXCreateCubeTextureFromFile(m_pDX9_Device,
			_szPath.c_str(),
			(LPDIRECT3DCUBETEXTURE9*)&TexTemp)))
		{
			return E_FAIL;
		}

	}
	else
	{
		//Image �ؽ��� �ҷ��ö�
		//��������Ʈ ��ü���� ��� �� ���� ������ �̹��� ���� �����صα�
		
		ImageInfoTemp = new D3DXIMAGE_INFO;

		if (FAILED(D3DXGetImageInfoFromFile(_szPath.c_str(), ImageInfoTemp)))
		{
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFile(m_pDX9_Device,
			_szPath.c_str(),
			(LPDIRECT3DTEXTURE9*)&TexTemp)))
		{
			return E_FAIL;
		}


	}


	m_vecTexturePair.emplace_back(pair<IDirect3DBaseTexture9*, D3DXIMAGE_INFO*>(TexTemp, ImageInfoTemp));

	//m_vecTextures.emplace_back(TexTemp);

	return S_OK;
}
