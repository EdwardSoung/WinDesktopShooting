#pragma once
#include "Actor.h"

constexpr int HouseVerticesCount = 7;
//집모양 그려주는 클래스
class TestHouseActor : public Actor
{
public:
	TestHouseActor(RenderLayer InLayer);
	virtual ~TestHouseActor();

	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;

private:
	const Gdiplus::PointF HouseVertices[HouseVerticesCount] =
	{
		{0,-100},{50,-50},{30,-50},{30,0},{-30,0},{-30,-50},{-50,-50}
	};
};

