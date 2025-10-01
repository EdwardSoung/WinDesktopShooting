#include "TestGridActor.h"
#include "Singleton.h"
#include "GameManager.h"

TestGridActor::TestGridActor(RenderLayer InLayer) : Actor(InLayer)
{
	OrangeBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 165, 100, 0));
}

TestGridActor::~TestGridActor()
{
	if (OrangeBrush)
	{
		delete OrangeBrush;
		OrangeBrush = nullptr;
	}
}

void TestGridActor::OnDraw(Gdiplus::Graphics* InGraphics)
{
	int Half = DotSize / 2;
	for (int i = 0; i <= Singleton<GameManager>::Instance().ScreenHeight; i += PixelDistance)
	{
		for (int j = 0; j <= Singleton<GameManager>::Instance().ScreenWidth; j += PixelDistance)
		{
			InGraphics->FillRectangle(OrangeBrush, j - Half, i - Half, DotSize, DotSize);
		}
	}
}