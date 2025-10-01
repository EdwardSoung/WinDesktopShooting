#pragma once
#include "framework.h"
#include "Actor.h"

class Background : public Actor
{
public:
	Background() = delete;
	Background(RenderLayer InLayer) : Actor(InLayer, ResourceType::Background)
	{
		InitPosition();
	}
	virtual ~Background();
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(double InDelatTime) override;
	virtual void InitPosition() override;

private:
	bool IsDraw = false;
	double ScrollSpeed = 50.0;
	float Offset = 0.0f;
};

