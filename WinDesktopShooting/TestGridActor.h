#pragma once
#include "Actor.h"

//50픽셀 단위로 점찍어주는 클래스
class TestGridActor : public Actor
{
public:
	TestGridActor();
	virtual ~TestGridActor();

	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;

private:
	Gdiplus::SolidBrush* OrangeBrush = nullptr;
	const int PixelDistance = 50;
	const int DotSize = 3;
};

