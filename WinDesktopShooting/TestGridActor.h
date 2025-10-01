#pragma once
#include "Actor.h"

//50�ȼ� ������ ������ִ� Ŭ����
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

