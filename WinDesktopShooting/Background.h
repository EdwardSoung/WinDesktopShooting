#pragma once
#include "framework.h"

//음..다른데 선언되어 있다
extern HWND g_hMainWindow;

class Background
{
public:
	Background() = delete;
	Background(IN Gdiplus::Point Size, IN const WCHAR* Path);
	~Background();
	void Draw(Gdiplus::Graphics* g_Graphics);
	void Scroll(Gdiplus::Graphics* g_Graphics, double deltaTime);

private:
	Gdiplus::Bitmap* Image = nullptr;               //플레이어 그릴 종이
	const int PixelSize = 64;
	Gdiplus::PointF Position;
	Gdiplus::Point ScreenSize;
	//Gdiplus::TextureBrush* Texture;

	bool IsDraw = false;

	double ScrollSpeed = 50.0;
	double ScrollDeltaY = 0;
};

