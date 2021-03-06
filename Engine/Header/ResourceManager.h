#pragma once

#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "Engine_Include.h"

#include "CResource.h"

class Texture;

//class StaticMesh;
//class AnimMesh;
class Mesh;
class NaviMesh;
class Shader;

class DLL_STATE ResourceManager
{
	Declare_Singleton(ResourceManager)

private:
	ResourceManager();
	virtual ~ResourceManager();

public:
	void Initialize(const wstring& _szResourceFolderPath = L"../../Resource/");
	void Update();
	void LateUpdate();
	void ReadyRender();
	void Release();

#pragma region Template
public:
	template<class KIND, class INSTANCE>
	KIND* Insert_Resource(const wstring& _wName)
	{
		string strKind = typeid(KIND).name();
		wstring wKind;
		wKind.assign(strKind.begin(), strKind.end());

		//string strInstance = typeid(INSTANCE).name();
		//wstring wInstance;
		//wInstance.assign(strInstance.begin(), strInstance.end());

 		auto iter_find = m_umResourceList[wKind].find(_wName);

		if (iter_find == m_umResourceList[wKind].end())
		{
			KIND* resource = new INSTANCE();
			//resource->Initialize();
			m_umResourceList[wKind][_wName] = resource;
			
			return resource;
		}
		else 
		{

			//같은 종류에서 같은 이름의 리소스가 존재한다. 이거야.
			return nullptr;

			//typedef unordered_map<wstring, CResource*> RESOURCE_LIST;
			////wstring : Name(Rect_Texture, Triangle_color), Resource : 객체
			//unordered_map<wstring, RESOURCE_LIST> m_umResourceList;
			////wstring : 종류 (ex)Mesh, VIBuffer, Material, Texture, Font등등)

			//wstring temp = L"'" + _wName + L"' is already Exist.";
			//int iChoose = MessageBox(NULL,
			//	L"Delete the existing resource and new one? = yes \nUse Existing resource = no" , 
			//	temp.c_str() ,MB_ICONWARNING| MB_YESNO);

			//if (iChoose == IDYES)
			//{//새로 만들기

			//	int Choose2 = MessageBox(NULL,
			//		L"U Choose Delete Existing resource. \nIf u were delete existing resource,That may Affecting Existing Mesh or Other Resorce.",
			//		L"R U Sure?", MB_ICONWARNING | MB_YESNO);

			//	if (Choose2 == IDYES)
			//	{
			//		m_umResourceList[wKind][_wName]->Release();
			//		Safe_Delete(m_umResourceList[wKind][_wName]);
			//		m_umResourceList[wKind].erase(iter_find);

			//		KIND* resource = new INSTANCE();
			//		//resource->Initialize();
			//		m_umResourceList[wKind][_wName] = resource;

			//		return resource;
			//		//이거 지금 이렇게 되면 원래 쓰던 텍스쳐는 사라져벌임.
			//	}
			//	else { goto NO; }
			//}
			//else 
			//{//기존꺼 쓰기
			//	NO:
			//	return (KIND*)m_umResourceList[wKind][_wName];
			//}
			//
		}
	}

	template<class T>
	T* Get_Resource(const wstring& _wName)
	{
		CResource* resource = nullptr;
			
		string strClass = typeid(T).name();
		wstring wClass;
		wClass.assign(strClass.begin(), strClass.end());

		auto iter_find = m_umResourceList[wClass].find(_wName);

		if (iter_find == m_umResourceList[wClass].end())
		{
			//assert(0 && L"Resource Can't find");
			return nullptr;
		}
		else 
		{
			resource = m_umResourceList[wClass][_wName];
		}

		return (T*)resource;
	}

	template<class T>
	void Delete_Resource()
	{
		
	}

#pragma endregion

public:
	void Load_AllResource();
	void Delete_AllResource();
	
	//Font
	void Load_Font();
	void Load_AllFonts();
	
	//Texture
	Texture*	Load_Texture(const wstring& _wPath, const wstring& _wName);
	Texture*	Add_Texture(Texture* _texture, const wstring& _wPath);

	void Load_ALLTextures();
	void Load_DDS();
	void Load_AllDDSs();
	
	//Meshes
	//StaticMesh* Load_StaticMesh(const wstring& _szMeshPath, const wstring& _szTexPath, const wstring& _szMeshName = L"");
	//AnimMesh*	Load_AnimMesh(const wstring& _szMeshPath, const wstring& _szMeshName = L"");
	Mesh*		Load_Mesh(const wstring& _szMeshPath, const wstring& _szMeshName);
	void		Load_AllMeshes();
	//void		Load_TerrainLayout(const wstring& _szDataPath);

	//Shader
	Shader*		Load_Shader(const wstring& _szShaderPath, const wstring& _szShaderName);

	//Default Resources
	void Insert_VIBuffers();
	void Insert_DefaultMeshes();
	void Insert_Shaders();
	
	//FilePath;
	wstring			EraseFolderPath(wstring _FullPath);
	wstring			EraseFileExtension(wstring _FileName);
public: /* Get */
	const wstring&	Get_ResourceFolderPath() const;
	NaviMesh*		Get_NaviMesh(const wstring& _szName)const;
	NaviMesh*		Get_NaviMeshClone();

public: /* Set */
	void Set_ResourceFolderPath(const wstring& _wPath);
	void Set_NaviMesh(NaviMesh* _pNaviMesh, const wstring& _szName);
	
private:
	typedef unordered_map<wstring, CResource*> RESOURCE_LIST;
	//wstring : Name(Rect_Texture, Triangle_color), Resource : 객체

	unordered_map<wstring, RESOURCE_LIST> m_umResourceList;
	//wstring : 종류 (ex)Mesh, VIBuffer, Material, Texture, Font등등)

private:
	wstring		m_wFolderPath;


	map<wstring, NaviMesh*>	m_pNaviMesh;
	//vector<NaviMesh*> m_pCloneNaviMesh;
	int				m_iNaviPointCount;
	Vector3*		m_arrNaviPointPosition;
	Vector3*		m_arrCellPointIndex;


};
#endif //_RESOURCE_MANAGER_H_
