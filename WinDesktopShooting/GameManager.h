#pragma once
#include <map>
#include <vector>
#include "framework.h"
#include "Actor.h"
#include "Player.h"
#include "Background.h"
#include "TestGridActor.h"
#include "TestHouseActor.h"

class GameManager
{
public:
	void Initialize();
	void Destroy();

	void Tick(float InDeltaTime);
	void Draw(HDC InHdc);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);
	void AddActor(Actor* InActor);

	static constexpr unsigned int ScreenWidth = 600;
	static constexpr unsigned int ScreenHeight = 800;
	static constexpr unsigned int ActorDefaultSize = 64;

	inline void UpdateWindow(HWND InWindow) {
		MainWindow = InWindow;
	}
	inline HWND GetMainWindow()
	{
		return MainWindow;
	}
	inline Gdiplus::Point GetAppPosition() { return AppPosition; }
protected:

private:

	std::map<RenderLayer, std::vector<Actor*>> Actors;
	HWND MainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(200, 100);

	//ȭ�� ������ �������� 2�� ����
	Gdiplus::Bitmap* BackBuffer = nullptr;                //�� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;      //�׸� ����

	Player* MainPlayer = nullptr;
};

