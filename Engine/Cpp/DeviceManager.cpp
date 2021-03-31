#include "..\Header\DeviceManager.h"


Implement_Singleton(DeviceManager)

DeviceManager::DeviceManager()
{
}

DeviceManager::~DeviceManager()
{
	Release();
}

void DeviceManager::Initialize(HWND _hWnd, UINT _wincx, UINT _wincy, bool _windowMode)
{
	m_vWindowSize.x = (float)_wincx;
	m_vWindowSize.y = (float)_wincy;

	if (Ready_DX9_Device(_hWnd, _wincx, _wincy, _windowMode) == E_FAIL)
	{
		assert(0 && L"Device Setting is failed");
	}

}

void DeviceManager::Release()
{
	Safe_Release(m_pDX9_Device);
	Safe_Release(m_pDX9_SDK);
}

HRESULT DeviceManager::Ready_DX9_Device(HWND _hWnd, UINT _wincx, UINT _wincy, bool _windowMode)
{
	D3DCAPS9 DeviceCap;//��ġ�� ���� ������ �����ؼ� ������ ������ ����ü.
					   //���� ��Ƽ������ ����Ҷ� �������ϸ� �����ִ� �κ��־ �������.

	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));

	m_pDX9_SDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_pDX9_SDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		//MessageBox(nullptr, L"CapFailed", L"System_Error", MB_OK);
		return E_FAIL;
	}

	DWORD	vp = 0;
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	//�ɱ� ���� or�������� ��Ƽ������ �߰��Ѱ� ������?���� �װŶ� �̰ž�

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//����ü�� ������ ����ϰڴ�.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//�� ���� ����.
	d3dpp.BackBufferWidth = _wincx;
	d3dpp.BackBufferHeight = _wincy;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //32��Ʈ���

	d3dpp.hDeviceWindow = _hWnd;

	//â��� ����
	d3dpp.Windowed = _windowMode;

	//��Ƽ���ø� ��� ���ϰڴ� �̰ž�
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	//���ٽ� ���
	d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.EnableAutoDepthStencil = eMode;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//�ֻ��� ����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //����Ʈ->�����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //�ÿ����� ����Ʈ


	if (FAILED(m_pDX9_SDK->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		vp,
		&d3dpp,
		&m_pDX9_Device
	)))
	{
		return E_FAIL;
	}


	return S_OK;
}

LPDIRECT3DDEVICE9 DeviceManager::Get_DX9_Device() const
{
	return m_pDX9_Device;
}

const Vector2 & DeviceManager::Get_WindowSize() const
{
	return m_vWindowSize;
}

#ifdef _DEBUG
HRESULT DeviceManager::Ready_DX9_Device_DEBUG(HWND _hWnd, UINT _wincx, UINT _wincy)
{
	D3DCAPS9 DeviceCap;//��ġ�� ���� ������ �����ؼ� ������ ������ ����ü.
					   //���� ��Ƽ������ ����Ҷ� �������ϸ� �����ִ� �κ��־ �������.

	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));

	m_pDX9_SDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_pDX9_SDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		//MessageBox(nullptr, L"CapFailed", L"System_Error", MB_OK);
		return E_FAIL;
	}

	DWORD	vp = 0;
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	//�ɱ� ���� or�������� ��Ƽ������ �߰��Ѱ� ������?���� �װŶ� �̰ž�

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//����ü�� ������ ����ϰڴ�.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//�� ���� ����.
	d3dpp.BackBufferWidth = _wincx;
	d3dpp.BackBufferHeight = _wincy;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //32��Ʈ���

	d3dpp.hDeviceWindow = _hWnd;

	//â��� ����
	d3dpp.Windowed = TRUE;

	//��Ƽ���ø� ��� ���ϰڴ� �̰ž�
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	//���ٽ� ���
	d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.EnableAutoDepthStencil = eMode;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//�ֻ��� ����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //����Ʈ->�����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //�ÿ����� ����Ʈ


	if (FAILED(m_pDX9_SDK->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		vp,
		&d3dpp,
		&m_pDX9_Device_DEBUG
	)))
	{
		return E_FAIL;
	}


	return S_OK;
}
LPDIRECT3DDEVICE9 DeviceManager::Get_DX9_Device_DEBUG() const
{
	return m_pDX9_Device_DEBUG;
}
#endif //_DEBUG




