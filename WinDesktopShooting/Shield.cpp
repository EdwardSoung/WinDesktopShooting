#include "Shield.h"
#include "GameManager.h"
Shield::~Shield()
{
    delete ShieldPen;
    ShieldPen = nullptr;
}

void Shield::OnInitialize()
{
    ShieldPen = new Gdiplus::Pen(Gdiplus::Color(100, 5, 71, 99), 6.0f);
}

void Shield::OnDraw(Gdiplus::Graphics* InGraphics)
{
    Gdiplus::Rect rc = 
        Gdiplus::Rect(
            static_cast<int>(Position.X - PixelSize * Pivot.X),
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);
    InGraphics->DrawArc(ShieldPen, rc, 160, 220);
}

void Shield::OnTick(float InDeltaTime)
{
	Position = GameManager::Instance().GetPlayerPosition();	
}

void Shield::OnOverlap(Actor* InOther)
{
}
