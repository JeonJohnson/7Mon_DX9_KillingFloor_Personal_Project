// Client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Client.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HWND	g_hWnd;
#ifdef _DEBUG
HWND	g_hWnd_DEBUG;
#endif //_DEBUG
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

												// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	msg.message = WM_NULL;

#ifdef _DEBUG //�����Ҵ� üũ �ϴ� �κ�. //Memory Leak Check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // DEBUG
	//Ŭ���� ���� ��� ���Ͽ� ���° �� �����µ�
	//�����ʿ��� ����� ���� �� ���ڸ� �����°�
	//���� �� �Լ��ȿ� �����ָ� �ű⼭ �ߴ��� �ɸ�.
	//_CrtSetBreakAlloc(5363);

	MainGame::Get_Instance()->Initialize();

	//int* temp = new int;

	// �⺻ �޽��� �����Դϴ�.
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		/* �츮 ���� ���� */
		MainGame::Get_Instance()->Process();
	}

	MainGame::Get_Instance()->Release();
	MainGame::Get_Instance()->Destroy_Instance();

	return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

#ifdef _DEBUG
	RECT	DebugWindow_rect = { 0,0,WINCX_DEBUG,WINCY_DEBUG };
	AdjustWindowRect(&DebugWindow_rect, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd_DEBUG = CreateWindowW(szWindowClass, L"Debug Window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		DebugWindow_rect.right - DebugWindow_rect.left,
		DebugWindow_rect.bottom - DebugWindow_rect.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd_DEBUG)
	{
		return FALSE;
	}

	g_hWnd_DEBUG = hWnd_DEBUG;

	SetWindowPos(hWnd_DEBUG, nullptr, (WINCX + 50), 0, 
		DebugWindow_rect.right - DebugWindow_rect.left,
		DebugWindow_rect.bottom - DebugWindow_rect.top, 0);

	ShowWindow(hWnd_DEBUG, nCmdShow);
	UpdateWindow(hWnd_DEBUG);
#endif //_DEBUG

	RECT rc = { 0, 0, WINCX, WINCY };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindowW(szWindowClass, L"Johnson3D", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 
		rc.right - rc.left, 
		rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	SetWindowPos(hWnd, nullptr, 0,0, rc.right-rc.left, rc.bottom - rc.top,  0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}