#pragma once
#include "framework.h"
#include "Enums.h"
#include <unordered_map>

//음..다른데 선언되어 있다
extern HWND g_hMainWindow;

class Player
{
public:
	Player() = delete;
	Player(IN Gdiplus::Point Size, IN const WCHAR* Path);
	~Player();

	void HandleKeyState(IN WPARAM Key, IN bool IsPressed);
	void Draw(Gdiplus::Graphics* g_Graphics);
	void Move(InputDirection InDirection);

private:
	Gdiplus::Bitmap* Image = nullptr;               //플레이어 그릴 종이
	const int PlayerPixelSize = 64;
	Gdiplus::PointF Position;
	Gdiplus::Point ScreenSize;
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };
	float PlayerSpeed = 10.0f;

	void InitPosition();
};

