#include "Shield.h"
#include "GameManager.h"

void Shield::OnInitialize()
{
    //�̹������� �̸� �ε�?

}

void Shield::OnDraw(Gdiplus::Graphics* InGraphics)
{
    //�̹����� ���� ������ ���� �ǵ� �̹����� ���'

    Actor::OnDraw(InGraphics);
    //Gdiplus::Rect rc = 
    //    Gdiplus::Rect(
    //        static_cast<int>(Position.X - PixelSize * Pivot.X),
    //        static_cast<int>(Position.Y - PixelSize * Pivot.Y),
    //        PixelSize, PixelSize);
    //InGraphics->DrawArc(ShieldPen, rc, 160, 220);
}

void Shield::OnTick(float InDeltaTime)
{
	Position = GameManager::Instance().GetPlayerPosition();	
}

void Shield::OnOverlap(Actor* InOther)
{
}
