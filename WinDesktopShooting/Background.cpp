#include "Background.h"
#include "GameManager.h"
#include "ResourceManager.h"

Background::~Background()
{
}

void Background::OnDraw(Gdiplus::Graphics* InGraphics)
{
    auto Image = Singleton<ResourceManager>::Instance().GetResource(ImageType);
    if (Image)
    {
        int newY = static_cast<int>(Position.Y - PixelSize * Pivot.Y + Offset);
        if (Offset > Singleton<GameManager>::Instance().ScreenHeight)
            Offset = -PixelSize;
    
        int xCount = Singleton<GameManager>::Instance().ScreenWidth / BorderSize() + 1;
        int yCount = Singleton<GameManager>::Instance().ScreenHeight / BorderSize() + 1;
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
