#include "..\Header\ResourceManager.h"
#include "VIBuffer.h"

//VIBuffers
#include "Rect_VIBuffer_Color.h"
#include "Rect_VIBuffer_Texture.h"

#include "Cube_VIBuffer_Color.h"
#include "Cube_VIBuffer_Texture.h"
#include "Cube_VIBuffer_DDS.h"
#include "Line_VIBuffer_Grid.h"
#include "Sphere_VIBuffer.h"

//Meshes
//#include "StaticMesh.h"
//#include "AnimMesh.h"
#include "Mesh.h"
#include "SphereCollider.h"

//shader
#include "Shader.h"
#include "NaviMesh.h"

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
	Insert_DefaultMeshes();
	Insert_Shaders();
}

void ResourceManager::Update()
{
	for (auto& resources : m_umResourceList)
	{
		for (auto& resource : resources.second)
		{
			resource.second->Update();
		}
	}
}

void ResourceManager::LateUpdate()
{
}

void ResourceManager::ReadyRender()
{
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


	//NaviMeshes;
}

void ResourceManager::Load_Font()
{

}

Texture* ResourceManager::Load_Texture(const wstring & _wPath, const wstring& _wName)
{
	Texture* TexTemp = Insert_Resource<Texture, Texture>(_wName);

	if (!TexTemp)
	{
		return nullptr;
	}

	//뒤에 확장자만 빼서 dds면 CubeFromFile로 불러올라고 
	wstring szFullPath = m_wFolderPath + _wPath;
		
	size_t DotPos = szFullPath.rfind(L".", szFullPath.length()-1);

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

Texture* ResourceManager::Add_Texture(Texture * _texture, const wstring & _wPath)
{
	wstring szFullPath = m_wFolderPath + _wPath;

	HRESULT _result	=  _texture->Insert_Texture(szFullPath, TEXTURE_KIND::Texture_Image);

	if (_result == E_FAIL)
	{
		return nullptr;
	}
	
	return _texture;
		
}

//StaticMesh * ResourceManager::Load_StaticMesh(const wstring& _szMeshPath, const wstring& _szTexPath, const wstring& _szMeshName)
//{
//	StaticMesh* StaticMeshTemp = Insert_Resource<StaticMesh, StaticMesh>(_szMeshName);
//
//	wstring szMeshFullPath = m_wFolderPath + _szMeshPath;
//	wstring szTextureFullPath = m_wFolderPath + _szTexPath;
//	
//	StaticMeshTemp->Insert_StaticMesh(szMeshFullPath, szTextureFullPath);
//	
//	return StaticMeshTemp;
//}
//
//AnimMesh * ResourceManager::Load_AnimMesh(const wstring & _szMeshPath, const wstring & _szMeshName)
//{
//	AnimMesh* AnimMeshTemp = Insert_Resource<AnimMesh, AnimMesh>(_szMeshName);
//	
//	wstring szMeshFullPath = m_wFolderPath + _szMeshPath;
//
//	AnimMeshTemp->Insert_AnimationMesh(szMeshFullPath, L"Test_AnimMesh");
//	
//	return nullptr;
//}


Mesh* ResourceManager::Load_Mesh(const wstring & _szMeshPath, const wstring & _szMeshName)
{
	Mesh* MeshTemp = Insert_Resource<Mesh, Mesh>(_szMeshName);

	if (!MeshTemp)
	{
		return nullptr;
	}

	wstring szMeshFullPath = m_wFolderPath + _szMeshPath;
	
	MeshTemp->Insert_Mesh(szMeshFullPath, _szMeshName);
	
	return MeshTemp;
}

Shader * ResourceManager::Load_Shader(const wstring & _szShaderPath, const wstring & _szShaderName)
{
	Shader* ShaderTemp = Insert_Resource<Shader, Shader>(_szShaderName);

	if (!ShaderTemp)
	{
		return nullptr;
	}

	wstring szShaderFullPath = m_wFolderPath + _szShaderPath;

	ShaderTemp->Insert_Shader(szShaderFullPath);

	return ShaderTemp;
}

void ResourceManager::Insert_VIBuffers()
{

	{ //Lines
		Insert_Resource<VIBuffer, Line_VIBuffer_Grid>(L"Line_Grid");

	}
	

	{ //Rects
		Insert_Resource<VIBuffer, Rect_VIBuffer_Color>(L"Rect_Color");
		Insert_Resource<VIBuffer, Rect_VIBuffer_Texture>(L"Rect_Texture");

	}


	{ //Cubes
		Insert_Resource<VIBuffer, Cube_VIBuffer_Color>(L"Cube_Color");
		Insert_Resource<VIBuffer, Cube_VIBuffer_Texture>(L"Cube_Texture");
		Insert_Resource<VIBuffer, Cube_VIBuffer_DDS>(L"Cube_DDS");
	}

	{
		Insert_Resource<VIBuffer, Sphere_VIBuffer>(L"Sphere_Debug");
	}


}

void ResourceManager::Insert_DefaultMeshes()
{
	Load_Mesh(L"Mesh/Static/DebugSphere.X", L"DebugSphere");
	Load_Mesh(L"Mesh/Static/DebugArrow.X", L"DebugArrow");
}

void ResourceManager::Insert_Shaders()
{
	Load_Shader(L"Shader/Debug_VIBuffer.fx", L"Debug_VIBuffer");

	Load_Shader(L"Shader/Shader_Mesh.fx", L"Shader_Mesh");

	Load_Shader(L"Shader/Shader_Sample.fx", L"Shader_Sample");

	Load_Shader(L"Shader/Effect_VIBuffer.fx", L"Effect_VIBuffer");

	Load_Shader(L"Shader/Effect_Fire.fx", L"Effect_Fire");

	Load_Shader(L"Shader/Effect_Trace.fx", L"Effect_Trace");
}

wstring ResourceManager::EraseFolderPath(wstring _FullPath)
{
	//L"../../Resource/"  지워주는거
	size_t folderPathLen = m_wFolderPath.length();
	wstring Temp = _FullPath.erase(0, folderPathLen);
	return Temp;
}

wstring ResourceManager::EraseFileExtension(wstring _FileName)
{

	size_t DotPos = _FileName.rfind(L".", _FileName.length() - 1);
	wstring szTemp = _FileName.erase(DotPos);
	//wstring szExtension = _FileName.substr(DotPos, _FileName.length());
	
	return szTemp;
}

const wstring & ResourceManager::Get_ResourceFolderPath() const
{
	return m_wFolderPath;
}

NaviMesh* ResourceManager::Get_NaviMesh(const wstring& _szName) const
{

	auto iter_find = m_pNaviMesh.find(_szName);

	if (iter_find == m_pNaviMesh.end())
	{
		return nullptr;
	}

	return (*iter_find).second;
}

NaviMesh * ResourceManager::Get_NaviMeshClone()
{
	NaviMesh*	CloneNaviMesh = new NaviMesh;

	return CloneNaviMesh;
}

void ResourceManager::Set_ResourceFolderPath(const wstring & _wPath)
{//상대경로로 폴더까지만 불러오자.
	m_wFolderPath = _wPath;
}

void ResourceManager::Set_NaviMesh(NaviMesh * _pNaviMesh, const wstring& _szName)
{
	assert(L"NaviMehs is Failed " && _pNaviMesh);

	//m_pNaviMesh = _pNaviMesh;
	m_pNaviMesh.emplace(_szName, _pNaviMesh);
}
