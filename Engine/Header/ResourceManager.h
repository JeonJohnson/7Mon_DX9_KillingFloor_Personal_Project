#pragma once

#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "Engine_Include.h"

#include "CResource.h"

class DLL_STATE ResourceManager
{
	Declare_Singleton(ResourceManager)

private:
	ResourceManager();
	virtual ~ResourceManager();

public:
	void Initialize();
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
			assert(0 && L"Resource is already created");
			//MessageBox(NULL, (L"Resource is already created by '" + _wName + L"'").c_str(), NULL, MB_OK);
			return nullptr;
			
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
			assert(0 && L"Resource Can't find");
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
	
	void Load_Font();
	void Load_AllFonts();
	
	void Load_Texture(const wstring& _wPath, const wstring& _wName);
	void Load_ALLTextures();
	
	void Load_DDS();
	void Load_AllDDSs();
	
	void Load_Mesh();
	void Load_AllMeshs();

	void Insert_VIBuffers();
	
public: /* Get */

public: /* Set */
	void Set_ResourceFolderPath(const wstring& _wPath);

	
private:
	typedef unordered_map<wstring, CResource*> RESOURCE_LIST;
	//wstring : Name(Rect_Texture, Triangle_color), Resource : ��ü

	unordered_map<wstring, RESOURCE_LIST> m_umResourceList;
	//wstring : ���� (ex)Mesh, VIBuffer, Material, Texture, Font���)

private:
	wstring		m_wFolderPath;
};
#endif //_RESOURCE_MANAGER_H_
