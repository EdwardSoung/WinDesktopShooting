// WinDesktopShooting.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinDesktopShooting.h"
#include "Enums.h"
#include "GameManager.h"

#include <crtdbg.h>
#include <unordered_map>
#include <chrono>
//#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

LARGE_INTEGER prevTick, currentTick;
double frameTime;
double fps;
double deltaTime = 0;

// 윈도우 64bit 시스템을 위한 QueryPerformanceFrequency
LARGE_INTEGER frequency;



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //Gdiplus 초기화 -> 종료 필요
    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput, nullptr);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDESKTOPSHOOTING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);                                                                             //1. 윈도우 클래스 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))                                                                //2. 윈도우 생성 및 초기화
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDESKTOPSHOOTING));

    MSG msg;

    QueryPerformanceFrequency(&frequency); // 타이머 주파수 얻기

    // 기본 메시지 루프입니다:                                                                                3. 메시지 루프
    //std::chrono::steady_clock::time_point Prev = std::chrono::steady_clock::now();
    while (true)
    {
        //auto Current = std::chrono::steady_clock::now();
        QueryPerformanceCounter(&currentTick); // 현재 시간 가져오기

        // 프레임 시간 계산 (마이크로초 단위)
        frameTime = (currentTick.QuadPart - prevTick.QuadPart) * 1000000.0 / frequency.QuadPart;

        // FPS 계산 (초 단위)
        fps = 1000000.0 / frameTime;
        deltaTime = 1.0 / fps;
                    
        //Message Queue가 없어도 한번 확인
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        GameManager::GetInstance().Tick(deltaTime);

        InvalidateRect(GameManager::GetInstance().GetMainWindow(), nullptr, FALSE);

        prevTick = currentTick;
    }

    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/

    //Gdiplus 정리
    Gdiplus::GdiplusShutdown(Token);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDESKTOPSHOOTING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;// MAKEINTRESOURCEW(IDC_WINDESKTOPSHOOTING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //클라이언트 영역(타이틀 부분 제외) 크기를 원하는 크기로 조절
   RECT rc = { 0, 0, GameManager::GetInstance().ScreenWidth, GameManager::GetInstance().ScreenHeight };
   //윈도우 스타일에 맞는 rect 가져옴
   AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
       FALSE, 0);


   auto mainWindow = CreateWindowW(szWindowClass, L"2D Shooting for GDI+"/*szTitle*/,
       WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,      //WS_MAXIMIZEBOX : 최대화 버튼 , WS_THICKFRAME 창 크기조절 선택
       GameManager::GetInstance().GetAppPosition().X, GameManager::GetInstance().GetAppPosition().Y,  //시작 좌표
       rc.right - rc.left, rc.bottom - rc.top,  //윈도우 스타일에 맞춰 재조정된 크기
       nullptr, nullptr, hInstance, nullptr);

   if (!mainWindow)
   {
      return FALSE;
   }

   GameManager::GetInstance().UpdateWindow(mainWindow);

   ShowWindow(mainWindow, nCmdShow);
   UpdateWindow(mainWindow);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //윈도우가 생성되었을 때
    case WM_CREATE:
        GameManager::GetInstance().Initialize();      

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            GameManager::GetInstance().Draw(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
        //입력 처리
    case WM_KEYDOWN:
    {
        GameManager::GetInstance().HandleKeyState(wParam, true);
        switch (wParam)
        {        
        case VK_ESCAPE:
            DestroyWindow(hWnd);
        }
    }       
        break;
    case WM_ERASEBKGND:
        //화면을 지워야 할 때 발생하는 메시지

        //지우지 않고 넘김
        return 1;
    case WM_KEYUP:
        GameManager::GetInstance().HandleKeyState(wParam, false);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//실습
//1. 집모양을 그리고 키보드 입력으로 상하좌우 움직이기
//2. 누르고 있으면 한번만 움직여야 한다.

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
