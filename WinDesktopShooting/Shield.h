#pragma once
#include "Actor.h"
class Shield :
    public Actor
{
	public:
	Shield() = delete;
	Shield(ResourceType InType) : Actor(InType)
	{
	}
	virtual ~Shield();

	virtual void OnInitialize() override;
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(float InDeltaTime) override;
	virtual void OnOverlap(Actor* InOther) override;

private:
	Gdiplus::Pen* ShieldPen;
	int ShieldCount = 3;

};

