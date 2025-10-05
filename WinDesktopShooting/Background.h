#pragma once
#include "framework.h"
#include "Actor.h"
#include <vector>

//음...라인(가로)만 그리고
//라인들을 아래 끝 도착하면 위에 그려주면 안될지..?
class Background : public Actor
{
public:
	Background() = delete;
	Background(ResourceType InType);

	virtual void OnInitialize() override;
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(float InDelatTime) override;

private:
	int XCount = 0;
	int YCount = 0;
	std::vector<int> YPositions;
};

