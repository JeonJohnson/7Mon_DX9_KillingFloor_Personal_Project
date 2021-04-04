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

vector<IDirect3DBaseTexture9*> Texture::Get_Textures()
{
	return m_vecTextures;
}

IDirect3DBaseTexture9 * Texture::Get_Texture(int _iNum = 0)
{
	size_t VecSize = m_vecTextures.size();

	if ((size_t)_iNum < VecSize)
	{
		return m_vecTextures[_iNum];
	}
	else { return nullptr; }
}

HRESULT Texture::Insert_Texture(const wstring & _szPath)
{
	IDirect3DBaseTexture9*	TexTemp = nullptr;
	
	//TCHAR szFullPath[128] = L"../../Resource/Test/boss.png";

	if(FAILED(D3DXCreateTextureFromFile(m_pDX9_Device, 
		_szPath.c_str(),
		(LPDIRECT3DTEXTURE9*)&TexTemp)))
	{
		return E_FAIL;
	}

	m_vecTextures.emplace_back(TexTemp);

	return S_OK;
}
