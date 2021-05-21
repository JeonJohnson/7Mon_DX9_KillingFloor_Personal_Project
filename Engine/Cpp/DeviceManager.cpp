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
	m_hWnd = _hWnd;

	if (Ready_DX9_Device(_hWnd, _wincx, _wincy, _windowMode) == E_FAIL)
	{
		assert(0 && L"Device Setting is failed");
	}

	if (FAILED(Ready_DX9_SpriteCom()))
	{
		assert(0 && L"Sprite Setting is Failed");
	}

}

void DeviceManager::Release()
{
	Safe_Release(m_pDX9_Sprite)
#ifdef _DEBUG
		Safe_Release(m_pDX9_Device_DEBUG);
#endif//_DEBUG
	Safe_Release(m_pDX9_Device);
	Safe_Release(m_pDX9_SDK);
}

HRESULT DeviceManager::Ready_DX9_Device(HWND _hWnd, UINT _wincx, UINT _wincy, bool _windowMode)
{
	D3DCAPS9 DeviceCap;//장치의 지원 수준을 조사해서 데이터 보관한 구조체.
					   //지금 멀티쓰레드 사용할때 설정안하면 버그있는 부분있어서 만들어줌.

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
	//쪼기 옆에 or연산으로 멀티쓰레드 추가한거 보이져?ㅇㅇ 그거라 이거야

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//스왑체인 형식을 사용하겠다.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//백 버퍼 세팅.
	d3dpp.BackBufferWidth = _wincx;
	d3dpp.BackBufferHeight = _wincy;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //32비트사용

	d3dpp.hDeviceWindow = _hWnd;

	//창모드 유무
#ifdef _DEBUG
	d3dpp.Windowed = _windowMode;
#else
	d3dpp.Windowed = FALSE;
#endif //_DEUBG


	//멀티샘플링 사용 안하겠다 이거야
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	//스텐실 사용
	d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.EnableAutoDepthStencil = eMode;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D32;

	//주사율 설정
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //화면
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //프레임 레이트 기본 값으로 설정.
											//=> DIRECT가 알아서 적정 프레임 골라서 정해줌.
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //모니터 주사율에 프레임 맞춤
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //프레임 레이트 제한 없음.
	//=> Device가 2개이상이면 모두들 이 설정이 되어있어야 제한 해제됨. 하나라도 걸려있으면 그거 따라감.

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

HRESULT DeviceManager::Ready_DX9_SpriteCom()
{
	if (FAILED(D3DXCreateSprite(m_pDX9_Device, &m_pDX9_Sprite)))
	{
		return E_FAIL;
	}
	
	return S_OK;
}

LPDIRECT3DDEVICE9 DeviceManager::Get_DX9_Device() const
{
	return m_pDX9_Device;
}

LPD3DXSPRITE DeviceManager::Get_DX9_Sprite() const
{
	return m_pDX9_Sprite;
}

const Vector2 & DeviceManager::Get_WindowSize() const
{
	return m_vWindowSize;
}

HWND DeviceManager::Get_HWND()
{
	return m_hWnd;
}

#ifdef _DEBUG
HRESULT DeviceManager::Ready_DX9_Device_DEBUG(HWND _hWnd, UINT _wincx, UINT _wincy)
{

	m_vWindowSize_DEBUG.x = (float)_wincx;
	m_vWindowSize_DEBUG.y = (float)_wincy;

	D3DCAPS9 DeviceCap;//장치의 지원 수준을 조사해서 데이터 보관한 구조체.
					   //지금 멀티쓰레드 사용할때 설정안하면 버그있는 부분있어서 만들어줌.

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
	//쪼기 옆에 or연산으로 멀티쓰레드 추가한거 보이져?ㅇㅇ 그거라 이거야

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//스왑체인 형식을 사용하겠다.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//백 버퍼 세팅.
	d3dpp.BackBufferWidth = _wincx;
	d3dpp.BackBufferHeight = _wincy;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //32비트사용

	d3dpp.hDeviceWindow = _hWnd;

	//창모드 유무
	d3dpp.Windowed = TRUE;

	//멀티샘플링 사용 안하겠다 이거야
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	//스텐실 사용
	d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.EnableAutoDepthStencil = eMode;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D32;

	//주사율 설정
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //화면
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //프레임 레이트 기본 값으로 설정.
														//=> DIRECT가 알아서 적정 프레임 골라서 정해줌.
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //모니터 주사율에 프레임 맞춤
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //프레임 레이트 제한 없음.
	//=> Device가 2개이상이면 모두들 이 설정이 되어있어야 제한 해제됨. 하나라도 걸려있으면 그거 따라감.

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
const Vector2 & DeviceManager::Get_WindowSize_DEBUG() const
{
	return m_vWindowSize_DEBUG;
}
#endif //_DEBUG




