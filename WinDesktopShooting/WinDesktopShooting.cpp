// WinDesktopShooting.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinDesktopShooting.h"

#include <crtdbg.h>
#include <string>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

int KEY_DOWN = 0;
Gdiplus::Point HouseStartPoint(0, 0);
const int WindowHeight = 300;
const int WindowWidth = 400;

const int RoofWidth = 160;
const int RoofHeight = 60;

const int WallWidth = 120;
const int WallHeight = 80;

constexpr UINT WM_APP_KEYUP_WITH_DATA = WM_APP + 1;

struct KeyUpPayload {
    UINT vk;      // 어떤 키였는지
    int  tag;     // 원하는 부가 데이터
    // 필요한 만큼 필드 추가 (동일 프로세스 내 포인터 OK)
};

void OnKeyUpForward(HWND hwnd, UINT vk, int tag) {
    auto* payload = new KeyUpPayload{ vk, tag };
    PostMessage(hwnd, WM_APP_KEYUP_WITH_DATA,
        static_cast<WPARAM>(vk),
        reinterpret_cast<LPARAM>(payload));
}

int TitleBarHeight = GetSystemMetrics(SM_CYCAPTION);

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
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

   HWND hWnd = CreateWindowW(szWindowClass, L"2D Shooting for GDI+"/*szTitle*/,
       WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,      //WS_MAXIMIZEBOX : 최대화 버튼 , WS_THICKFRAME 창 크기조절 선택
       200/*CW_USEDEFAULT*/, 100/*0*/,  //시작 좌표
       WindowWidth/*CW_USEDEFAULT*/, WindowHeight/*0*/,  //사이즈
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
    int Limit = 0;
    switch (message)
    {
    //case WM_APP_KEYUP_WITH_DATA: {
    //    auto* p = reinterpret_cast<KeyUpPayload*>(lParam);
    //
    //    switch (p->vk)
    //    {
    //    case VK_UP:
    //        OutputDebugStringW(L"KEY UP!!\n");
    //        break;
    //    }
    //    delete p; // 소유권/수명 관리 확실히
    //    return 0;
    //}
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
            Gdiplus::Graphics GraphicsInstance(hdc);

            Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
            Gdiplus::SolidBrush BlueBrush(Gdiplus::Color(255, 0, 0, 255));
            Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 255, 255, 255));
            Gdiplus::SolidBrush GreenBrush(Gdiplus::Color(255, 100, 255, 100));
            Gdiplus::SolidBrush BrownBrush(Gdiplus::Color(255, 165, 42, 42));
            Gdiplus::SolidBrush LightBrownBrush(Gdiplus::Color(255, 77, 59, 37));
            Gdiplus::SolidBrush SkyBlueBrush(Gdiplus::Color(255, 173, 216, 230));
            Gdiplus::Pen BlackPen(Gdiplus::Color(255, 0, 0, 0));
            Gdiplus::Pen WhitePen(Gdiplus::Color(255, 255, 255, 255));


            GraphicsInstance.FillRectangle(&SkyBlueBrush, 0, 0, WindowWidth, WindowHeight);
            GraphicsInstance.FillEllipse(&LightBrownBrush, -(WindowWidth / 2), WindowHeight / 2 + 30, WindowWidth * 2, WindowHeight);
            
            //GraphicsInstance.FillRectangle(&RedBrush, 0, 0, 60, 120);
            ////파란색 원
            //GraphicsInstance.FillEllipse(&BlueBrush, 80, 0, 80, 80);
            ////기타 도형
            //GraphicsInstance.FillPie(&RedBrush, 0, 140, 80, 80, Gdiplus::REAL(270), Gdiplus::REAL(-180));

            GraphicsInstance.FillRectangle(&BrownBrush, 200, 120, 20, 80);
            GraphicsInstance.FillEllipse(&GreenBrush, 200, 40, 20, 40);
            GraphicsInstance.FillEllipse(&GreenBrush, 190, 60, 40, 50);
            GraphicsInstance.FillEllipse(&GreenBrush, 180, 80, 60, 80);

            Gdiplus::Rect WallRect(HouseStartPoint.X + (RoofWidth - WallWidth) / 2, HouseStartPoint.Y + RoofHeight, WallWidth, WallHeight);
            GraphicsInstance.FillRectangle(&WhiteBrush, WallRect);
            //집 모양 만들기
            //지붕
            Gdiplus::Point* RoofPoints = new Gdiplus::Point[3]
            {
                Gdiplus::Point(HouseStartPoint.X + RoofWidth / 2, HouseStartPoint.Y),           //꼭대기
                Gdiplus::Point(HouseStartPoint.X, HouseStartPoint.Y + RoofHeight),              //좌측
                Gdiplus::Point(HouseStartPoint.X + RoofWidth, HouseStartPoint.Y + RoofHeight)   //우측
            };
            GraphicsInstance.FillPolygon(&BlueBrush, RoofPoints, 3);

            Gdiplus::Point* WallPoints = new Gdiplus::Point[4]
            {
                Gdiplus::Point(HouseStartPoint.X + (RoofWidth - WallWidth) / 2, HouseStartPoint.Y + RoofHeight),
                Gdiplus::Point(HouseStartPoint.X + (RoofWidth - WallWidth) / 2, HouseStartPoint.Y + RoofHeight + WallHeight),
                Gdiplus::Point(HouseStartPoint.X + RoofWidth - (RoofWidth - WallWidth) / 2, HouseStartPoint.Y + RoofHeight + WallHeight),
                Gdiplus::Point(HouseStartPoint.X + RoofWidth - (RoofWidth - WallWidth) / 2, HouseStartPoint.Y + RoofHeight)
            };
            
            GraphicsInstance.DrawLines(&BlackPen, WallPoints, 4);

            EndPaint(hWnd, &ps);
        }
        break;
        //입력 처리
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            //VK : Virtual Key            
        case VK_UP:
            //OnKeyUpForward(hWnd, wParam, HouseStartPoint.Y);
            //0번 자리가 0이면
            if ((KEY_DOWN & (1 << 1)) != (1 << 1))
            {
                KEY_DOWN |= 1 << 1;
                if (HouseStartPoint.Y > 0)
                    HouseStartPoint.Y -= 5;

                InvalidateRect(hWnd, nullptr, TRUE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            break;
        case VK_DOWN:
            if ((KEY_DOWN & (1 << 2)) != (1 << 2))
            {
                KEY_DOWN |= 1 << 2;

                if (HouseStartPoint.Y < WindowHeight - (RoofHeight + WallHeight + TitleBarHeight))
                    HouseStartPoint.Y += 5;
                OutputDebugStringA((std::to_string(HouseStartPoint.Y) + ", " + std::to_string(Limit)).c_str());
                OutputDebugStringA("\n");

                InvalidateRect(hWnd, nullptr, TRUE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            
            break;
        case VK_LEFT:
            if ((KEY_DOWN & (1 << 2)) != (1 << 3))
            {
                if (HouseStartPoint.X > 0)
                    HouseStartPoint.X -= 5;
                InvalidateRect(hWnd, nullptr, TRUE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            KEY_DOWN |= 1 << 3;

            break;
        case VK_RIGHT:
            if ((KEY_DOWN & (1 << 4)) != (1 << 4))
            {
                KEY_DOWN |= 1 << 4;

                if (HouseStartPoint.X < WindowWidth - RoofWidth)
                    HouseStartPoint.X += 5;

                InvalidateRect(hWnd, nullptr, TRUE);        //창을 다시 그려줌(WM_PAINT 메시지 처리)
            }
            break;
        case VK_ESCAPE:
            DestroyWindow(hWnd);
        }
    }       
        break;
    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_UP:
            KEY_DOWN &= ~(1 << 1);
            break;
        case VK_DOWN:
            KEY_DOWN &= ~(1 << 2);
            break;
        case VK_LEFT:
            KEY_DOWN &= ~(1 << 3); 
            break;
        case VK_RIGHT:
            KEY_DOWN &= ~(1 << 4);
            break;
        }
    }
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
