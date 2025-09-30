#include "Background.h"

Background::Background(IN Gdiplus::Point Size, IN const WCHAR* Path)
{
    ScreenSize = Size;
    Image = new Gdiplus::Bitmap(Path);
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        //플레이어 이미지 정상 로딩 실패
        delete Image;
        Image = nullptr;
        //MessageBox(hWnd, L"플레이어 이미지 로드 실패", L"Error", MB_OK | MB_ICONERROR);
    }
    //Texture = new Gdiplus::TextureBrush(Image);
}

Background::~Background()
{
    delete Image;
    Image = nullptr;

    delete Texture;
    Texture = nullptr;
}

void Background::Draw(Gdiplus::Graphics* g_Graphics)
{    
    int xCount = ScreenSize.X / PixelSize + 1;
    int yCount = ScreenSize.Y / PixelSize + 1;
    //g_Graphics->FillRectangle(Texture, 0, 0, ScreenSize.X, ScreenSize.Y);
    //Texture->TranslateTransform(0, 0.5f);
    for (int i = -yCount; i < yCount; i++)
    {
        for (int j = 0; j < xCount; j++)
        {
            g_Graphics->DrawImage(Image, j * PixelSize, i * PixelSize + ScrollDeltaY, PixelSize, PixelSize);

            //g_Graphics->TranslateTransform(j * PixelSize, i * PixelSize + ScrollDeltaY);
        }
    }
    //IsDraw = true;
}

void Background::Scroll(Gdiplus::Graphics* g_Graphics, double deltaTime)
{
    if (ScrollDeltaY >= (ScreenSize.Y / PixelSize) * PixelSize)
        ScrollDeltaY = 0;
    else
    {
        ScrollDeltaY += deltaTime * ScrollSpeed;
    }
   
}
