#include "..\Header\CResource.h"
#include "DeviceManager.h"


CResource::CResource()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
}


CResource::~CResource()
{
}

void CResource::Update()
{
}
