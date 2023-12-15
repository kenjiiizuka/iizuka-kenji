#include "Application.h"
#include "../main.h"
#include "Manager.h"
#include "System/RendererSystem/Renderer.h"
#include "System/FPSController/FPSController.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "../resource.h"

const wchar_t* ClassName = TEXT("EnemyMaker");
const wchar_t* WindowName = TEXT("EnemyMaker");

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Application::Application(float _width, float _height)
	: mHInstance   (nullptr)
	, mhWnd    (nullptr)
	, mWidth   (_width)
	, mHeight  (_height)
{
	// 処理なし
}

Application::~Application()
{
	// 処理なし
}

void Application::Run()
{
	if (Initialize())
	{
		MainLoop();
	}
	Uninitialize();
}

bool Application::Initialize()
{
	if (!WindowInitialize())
	{
		return false;
	}
	// 正常終了
	return true;
}

void Application::Uninitialize()
{
	//COMの終了処理
	CoUninitialize();
	// ウィンドウの終了処理
	WindowUninitialize();
}

bool Application::WindowInitialize()
{
	// インスタンスハンドルを取得
	HINSTANCE hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr)
	{
		return false;
	}

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler,TRUE); // ConsoleWindowのハンドラーをセット
	
	// Windowの設定
	WNDCLASSEX wc = {};
	// wc.hIcon = LoadIcon(mHInstance, MAKEINTRESOURCE(IDI_ICON1));
	// wc.hIconSm = LoadIcon(mHInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.cbSize            = sizeof(WNDCLASSEX);
	wc.style             = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc       = WndProc;
	wc.hIcon             = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor           = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground     = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName      = nullptr;
	wc.lpszClassName     = ClassName;
	wc.hIconSm           = LoadIcon(hInst,IDI_APPLICATION);

	// ウィンドウの登録
	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	// インスタンスハンドル設定
	mHInstance = hInst;

	// ウィンドウのサイズ設定
	RECT rect = {};
	rect.right   = static_cast<LONG>(mWidth);
	rect.bottom  = static_cast<LONG>(mHeight);

	// ウィンドウサイズを調整
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rect, style, FALSE);
	
	// ウィンドウを生成
	mhWnd = CreateWindowEx(
		0,
		ClassName,
		WindowName,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		nullptr,
		nullptr,
		mHInstance,
		nullptr
	);

	if(mhWnd == nullptr)
	{
		return false;
	}

	// ウィンドウを表示
	ShowWindow(mhWnd, SW_SHOWNORMAL);

	// ウィンドウを更新
	UpdateWindow(mhWnd);

	// ウィンドウにフォーカスを設定
	SetFocus(mhWnd);

	// COMの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return false;
	}

	// 正常終了
	return true;
}

void Application::WindowUninitialize()
{
	// ウィンドウの登録の解除
	if (mHInstance != nullptr)
	{
		UnregisterClass(ClassName, mHInstance);
	}

	SetConsoleCtrlHandler(NULL, FALSE); // コンソールウィンドウに登録しているハンドル関数を解除

	mHInstance = nullptr;
	mhWnd  = nullptr;
}

void Application::MainLoop()
{
	MSG msg = {};
	timeBeginPeriod(1);
	Manager::Initialize(this);
	FPSController::Init(60);

	while ((WM_QUIT != msg.message) && Manager::IsActive())
	{
		if(PeekMessage(&msg,nullptr,0,0,PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			FPSController::StartFrame();
			Manager::Update();
			Manager::Draw();
		}
	}
	timeEndPeriod(1);
	Manager::Uninitialize();
}

LRESULT Application::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
		return DefWindowProc(hWnd, msg, wp, lp);

	switch (msg)
	{
		// 終了メッセージ処理
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
		break;
	default:
	{ /* Do Nothing */ }
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}

BOOL Application::CtrlHandler(DWORD ctrlType)
{
	if (ctrlType == CTRL_CLOSE_EVENT)
	{
		printf("終了");
		return TRUE;
	}
	return TRUE;
}

