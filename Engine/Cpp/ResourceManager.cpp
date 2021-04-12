#include "..\Header\ResourceManager.h"
#include "VIBuffer.h"

//VIBuffers
#include "Rect_VIBuffer_Color.h"
#include "Rect_VIBuffer_Texture.h"

#include "Cube_VIBuffer_Color.h"
#include "Cube_VIBuffer_Texture.h"
#include "Cube_VIBuffer_DDS.h"
#include "StaticMesh.h"


Implement_Singleton(ResourceManager)

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	Release();
}

void ResourceManager::Initialize(const wstring& _szResourceFolderPath)
{
	m_wFolderPath = _szResourceFolderPath;
	//m_wFolderPath = L"../../Resource/";
	Insert_VIBuffers();
}

void ResourceManager::Release()
{
	Delete_AllResource();
}

void ResourceManager::Load_AllResource()
{

}

void ResourceManager::Delete_AllResource()
{
	for (auto& Resources : m_umResourceList)
	{
		for (auto& Resource : Resources.second)
		{
			Resource.second->Release();
			Safe_Delete(Resource.second);
		}
		Resources.second.clear();
	}
	m_umResourceList.clear();


	//font 객체 해제들
}

void ResourceManager::Load_Font()
{

}

Texture* ResourceManager::Load_Texture(const wstring & _wPath, const wstring& _wName)
{
	Texture* TexTemp = Insert_Resource<Texture, Texture>(_wName);

	//뒤에 확장자만 빼서 dds면 CubeFromFile로 불러올라고 
	wstring szFullPath = m_wFolderPath + _wPath;
		
	size_t DotPos = szFullPath.rfind(L".", szFullPath.length()-1);
	
	//wstring sztemp;
	//sztemp = szFullPath.at(DotPos);
	wstring szExtension = szFullPath.substr(DotPos, szFullPath.length());

	TEXTURE_KIND textureKind;

	if (szExtension == L".dds")
	{
		textureKind = TEXTURE_KIND::Texture_DDS;
	}
	else 
	{
		textureKind = TEXTURE_KIND::Texture_Image;
	}


	if (FAILED(TexTemp->Insert_Texture(szFullPath, textureKind)))
	{
		MsgBox(L"Error", L"Texture Inserting is failed");
		return nullptr;
	}

	return TexTemp;
}

HRESULT ResourceManager::Add_Texture(Texture * _texture, const wstring & _wPath, const wstring & _wName)
{
	wstring szFullPath = m_wFolderPath + _wPath;

	if (FAILED(_texture->Insert_Texture(szFullPath, TEXTURE_KIND::Texture_Image)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void ResourceManager::Load_Mesh(const wstring & _szMeshPath, const wstring & _szTexPath)
{
	//StaticMesh* pStaticMesh = nullptr;
	
}

void ResourceManager::Insert_VIBuffers()
{
	{ //Rects
		Insert_Resource<VIBuffer, Rect_VIBuffer_Color>(L"Rect_Color");
		Insert_Resource<VIBuffer, Rect_VIBuffer_Texture>(L"Rect_Texture");

		//Grid

	}


	{ //Cube
		Insert_Resource<VIBuffer, Cube_VIBuffer_Color>(L"Cube_Color");
		Insert_Resource<VIBuffer, Cube_VIBuffer_Texture>(L"Cube_Texture");
		Insert_Resource<VIBuffer, Cube_VIBuffer_DDS>(L"Cube_DDS");
	}



}

const wstring & ResourceManager::Get_ResourceFolderPath() const
{
	return m_wFolderPath;
}

void ResourceManager::Set_ResourceFolderPath(const wstring & _wPath)
{//상대경로로 폴더까지만 불러오자.
	m_wFolderPath = _wPath;
}
