#include "TestGridActor.h"
#include "Singleton.h"
#include "GameManager.h"

TestGridActor::TestGridActor(ResourceType InType) : Actor(InType)
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
	for (int i = 0; i <= GameManager::Instance().ScreenHeight; i += PixelDistance)
	{
		for (int j = 0; j <= GameManager::Instance().ScreenWidth; j += PixelDistance)
		{
			InGraphics->FillRectangle(OrangeBrush, j - Half, i - Half, DotSize, DotSize);
		}
	}
}