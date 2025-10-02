#pragma once
#include "framework.h"
#include "Actor.h"

//음...라인(가로)만 그리고
//라인들을 아래 끝 도착하면 위에 그려주면 안될지..?
class Background : public Actor
{
public:
	Background() = delete;
	Background(ResourceType InType);

	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(double InDelatTime) override;

private:
	bool IsDraw = false;
	double ScrollSpeed = 50.0;
	float Offset = 0.0f;
};

