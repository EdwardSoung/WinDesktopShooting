#pragma once
#include "framework.h"
#include "Enums.h"
#include <unordered_map>

//��..�ٸ��� ����Ǿ� �ִ�
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
	Gdiplus::Bitmap* Image = nullptr;               //�÷��̾� �׸� ����
	const int PlayerPixelSize = 64;
	Gdiplus::PointF Position;
	Gdiplus::Point ScreenSize;
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };
	float PlayerSpeed = 10.0f;

	void InitPosition();
};

