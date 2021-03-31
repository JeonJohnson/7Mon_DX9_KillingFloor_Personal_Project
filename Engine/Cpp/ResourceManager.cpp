#include "..\Header\ResourceManager.h"
#include "VIBuffer.h"
#include "Rect_VIBuffer_Color.h"


Implement_Singleton(ResourceManager)

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::Initialize()
{
	Insert_VIBuffers();
}

void ResourceManager::Release()
{
	Delete_AllResource();
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


	//font ��ü ������
}

void ResourceManager::Load_Fonts()
{
}

void ResourceManager::Insert_VIBuffers()
{
	{ //Rect_color
		Insert_Resource<VIBuffer, Rect_VIBuffer_Color>(L"Rect_Color");
	}
}