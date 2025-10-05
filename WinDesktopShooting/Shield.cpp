#include "Shield.h"
#include "GameManager.h"

void Shield::OnInitialize()
{
    //이미지들을 미리 로드?

}

void Shield::OnDraw(Gdiplus::Graphics* InGraphics)
{
    //이미지를 남은 개수에 따른 실드 이미지로 출력'

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
