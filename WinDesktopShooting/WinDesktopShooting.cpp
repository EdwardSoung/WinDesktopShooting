// WinDesktopShooting.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinDesktopShooting.h"
#include "Enums.h"

#include <crtdbg.h>
#include <unordered_map>
//#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
Gdiplus::Point g_HousePosition(100, 100);
constexpr int g_HouseVerticesCount = 7;

Gdiplus::Point g_AppPosition(200, 100);
Gdiplus::Point g_ScreenSize(800, 600);

const Gdiplus::Point g_HouseVertices[g_HouseVerticesCount] =
{
    {0,-100},{50,-50},{30,-50},{30,0},{-30,0},{-30,-50},{-50,-50}
};
std::unordered_map<InputDirection, bool> g_KeyWasPressedMap;

//화면 깜박임 막기위한 2중 버퍼
Gdiplus::Bitmap* g_BackBuffer = nullptr;                //빈 종이
Gdiplus::Graphics* g_BackBufferGraphics = nullptr;      //그릴 도구

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

    g_KeyWasPressedMap[InputDirection::Up] = false;
    g_KeyWasPressedMap[InputDirection::Down] = false;
    g_KeyWasPressedMap[InputDirection::Left] = false;
    g_KeyWasPressedMap[InputDirection::Right] = false;

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

    // 기본 메시지 루프입니다:                                                                                3. 메시지 루프
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
   RECT rc = { 0, 0, g_ScreenSize.X, g_ScreenSize.Y };
   //윈도우 스타일에 맞는 rect 가져옴
   AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
       FALSE, 0);

   HWND hWnd = CreateWindowW(szWindowClass, L"2D Shooting for GDI+"/*szTitle*/,
       WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,      //WS_MAXIMIZEBOX : 최대화 버튼 , WS_THICKFRAME 창 크기조절 선택
       g_AppPosition.X, g_AppPosition.Y,  //시작 좌표
       rc.right - rc.left, rc.bottom - rc.top,  //윈도우 스타일에 맞춰 재조정된 크기
       nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
        g_BackBuffer = new Gdiplus::Bitmap(g_ScreenSize.X, g_ScreenSize.Y, PixelFormat32bppARGB);
        g_BackBufferGraphics = Gdiplus::Graphics::FromImage(g_BackBuffer);
        if (!g_BackBufferGraphics)
        {
            //안만들어졌으면 에러 출력
            MessageBox(hWnd, L"Back Buffer Graphics Gnenarate failed!", L"Error", MB_OK | MB_ICONERROR);
        }
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

            if (g_BackBufferGraphics)
            {
                g_BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
                
                Gdiplus::SolidBrush GreenBrush(Gdiplus::Color(255, 0, 255, 0));
                Gdiplus::SolidBrush BlueBrush(Gdiplus::Color(255, 0, 0, 255));
                Gdiplus::SolidBrush OrangeBrush(Gdiplus::Color(255, 255, 165, 0));
                
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        g_BackBufferGraphics->FillRectangle(&BlueBrush, 30 + 70 * j, 50 + 70 * i, 60, 60);
                    }
                }


                Gdiplus::Pen GreenPen(Gdiplus::Color(255, 0, 255, 0), 2.0f);
                Gdiplus::Point Positions[g_HouseVerticesCount];
                for (int i = 0; i < g_HouseVerticesCount; i++)
                {
                    Positions[i] = g_HousePosition + g_HouseVertices[i];
                }
                //GraphicsInstance.DrawPolygon(&GreenPen, Positions, g_HouseVerticesCount);
                g_BackBufferGraphics->FillPolygon(&GreenBrush, Positions, g_HouseVerticesCount);
                
                Gdiplus::Graphics GraphicsInstance(hdc);
                GraphicsInstance.DrawImage(g_BackBuffer, 0, 0);
            }

            EndPaint(hWnd, &ps);
        }
        break;
        //입력 처리
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            //VK : Virtual Key            
        case VK_LEFT:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
            {
                g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
                g_HousePosition.X -= 10;
                OutputDebugStringW(L"왼쪽키를 눌렀다.\n");
                InvalidateRect(hWnd, nullptr, FALSE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            break;
        case VK_RIGHT:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
            {
                g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
                g_HousePosition.X += 10;
                OutputDebugStringW(L"오른키를 눌렀다.\n");
                InvalidateRect(hWnd, nullptr, FALSE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            break;
        case VK_UP:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
            {
                g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
                g_HousePosition.Y -= 10;
                OutputDebugStringW(L"오른키를 눌렀다.\n");
                InvalidateRect(hWnd, nullptr, FALSE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            break;
        case VK_DOWN:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
            {
                g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
                g_HousePosition.Y += 10;
                OutputDebugStringW(L"오른키를 눌렀다.\n");
                InvalidateRect(hWnd, nullptr, FALSE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            break;
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
    {
        g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = false;
    }
        break;
    case WM_DESTROY:
        delete g_BackBufferGraphics;
        g_BackBufferGraphics = nullptr;
        delete g_BackBuffer;
        g_BackBuffer = nullptr;

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
