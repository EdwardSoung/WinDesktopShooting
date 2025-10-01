#pragma once
#include "framework.h"

class Actor
{
public:
	Actor() = delete;
	Actor(IN const WCHAR* Path);
	virtual ~Actor() {}

	virtual void OnDraw(Gdiplus::Graphics* InGraphics);
	virtual void OnTick(double InDeltaTime) {}
	virtual void InitPosition() {}

	inline int BorderSize() { return PixelSize - BorderPixel; }
	inline void UpdatePosition(Gdiplus::PointF InPosition)
	{
		Position = InPosition;
	}
	inline void UpdatePivot(float InX, float InY)
	{
		Pivot.X = InX;
		Pivot.Y = InY;
	}

protected:
	Gdiplus::Bitmap* Image = nullptr;               //플레이어 그릴 종이
	const int PixelSize = 64;
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };
	Gdiplus::PointF Position;

private:
	const int BorderPixel = 3;
};

