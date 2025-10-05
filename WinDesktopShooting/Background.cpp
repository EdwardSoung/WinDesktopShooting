#include "Background.h"
#include "GameManager.h"
#include "ResourceManager.h"


Background::Background(ResourceType InType) : Actor(InType)
{
    Pivot.X = 0;    // ¿ÞÂÊ À§°¡ ÇÇº¿
    Pivot.Y = 0;
}

void Background::OnInitialize()
{
    PixelSize = 256;
    XCount = GameManager::Instance().ScreenWidth / PixelSize + 1;
    YCount = GameManager::Instance().ScreenHeight / PixelSize + 1;

    for (int i = -1; i < YCount; i++)
    {
        YPositions.push_back(i * PixelSize);
    }
}

void Background::OnDraw(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        for (int newY : YPositions)
        {
            for (int j = 0; j < XCount; j++)
            {
                InGraphics->DrawImage(Image,
                    static_cast<int>(Position.X + PixelSize * j),
                    static_cast<int>(newY),
                    PixelSize, PixelSize);
            }
        }
    }
}

void Background::OnTick(float InDelatTime)
{
    for (int &y : YPositions)
    {
        y += 1;
        if (y >= PixelSize * YCount)
            y = -PixelSize;
    }
}
