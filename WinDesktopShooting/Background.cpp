#include "Background.h"
#include "GameManager.h"

Background::~Background()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Background::OnDraw(Gdiplus::Graphics* InGraphics)
{    
    if (Image)
    {
        int newY = static_cast<int>(Position.Y - PixelSize * Pivot.Y + Offset);
        if (newY > GameManager::GetInstance().ScreenHeight)
            Offset = -PixelSize;
    
        int xCount = GameManager::GetInstance().ScreenWidth / BorderSize() + 1;
        int yCount = GameManager::GetInstance().ScreenHeight / BorderSize() + 1;
        int TotalHeight = BorderSize() * yCount;

        for (int i = -1; i < yCount; i++)
        {
            for (int j = 0; j < xCount; j++)
            {
                InGraphics->DrawImage(Image,
                    static_cast<int>(Position.X - PixelSize * Pivot.X + BorderSize() * j),
                    static_cast<int>(newY),
                    PixelSize, PixelSize);
            }

            newY += BorderSize();
            if (newY > TotalHeight)
                newY -= (TotalHeight + BorderSize());
        }
    }
}

void Background::OnTick(double InDelatTime)
{
    Offset += 1.0f;
}

void Background::InitPosition()
{
    Position = Gdiplus::PointF(PixelSize * Pivot.X, PixelSize * Pivot.Y);
}
