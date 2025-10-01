#include "Actor.h"

Actor::Actor(IN const WCHAR* Path)
{
    if (Path == nullptr)
        return;

    Image = new Gdiplus::Bitmap(Path);
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        //�÷��̾� �̹��� ���� �ε� ����
        delete Image;
        Image = nullptr;
        //MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
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