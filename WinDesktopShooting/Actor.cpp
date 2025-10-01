#include "Actor.h"

Actor::Actor(IN const WCHAR* Path)
{
    if (Path == nullptr)
        return;

    Image = new Gdiplus::Bitmap(Path);
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        //플레이어 이미지 정상 로딩 실패
        delete Image;
        Image = nullptr;
        //MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
}

void Actor::OnDraw(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        InGraphics->DrawImage(Image,
            static_cast<int>(Position.X - PixelSize * Pivot.X),
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);
    }
}