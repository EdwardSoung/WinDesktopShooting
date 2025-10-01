#pragma once
#include "framework.h"
#include "Enums.h"

class Actor
{
public:
	Actor() = delete;
	Actor(RenderLayer InLayer, ResourceType InType = ResourceType::None);
	virtual ~Actor() {}

	virtual void OnDraw(Gdiplus::Graphics* InGraphics);
	virtual void OnTick(double InDeltaTime) {}
	virtual void InitPosition() {}

	//Getter
	inline int BorderSize() { return PixelSize - BorderPixel; }
	inline RenderLayer GetLayer() { return Layer; }

	//Setter
	inline void UpdatePosition(Gdiplus::PointF InPosition)
	{
		Position = InPosition;
	}
	inline void UpdatePivot(float InX, float InY)
	{
		Pivot.X = InX;
		Pivot.Y = InY;
	}
	inline void SetLayer(RenderLayer InLayer)
	{
		Layer = InLayer;
	}

protected:
	const int PixelSize = 64;
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };
	Gdiplus::PointF Position;
	ResourceType ImageType = ResourceType::None;

private:
	const int BorderPixel = 3;
	RenderLayer Layer = RenderLayer::Misc;
};

