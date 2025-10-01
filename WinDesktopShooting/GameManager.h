#pragma once
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
	static GameManager& GetInstance() {
		static GameManager Instance;
		return Instance;
	}
	void Initialize();
	void Destroy();

	void Tick(float InDeltaTime);
	void Draw(HDC InHdc);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

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
	GameManager() = default;		//기본 생성자를 private로 해서 생성불가
	GameManager(const GameManager&) = delete;		//복사 생성자 제거
	GameManager& operator=(const GameManager&) = delete; //대입 연산자 삭제
	GameManager(const GameManager&&) = delete;
	GameManager& operator=(const GameManager&&) = delete;		//이동대입연산자 제거

	std::vector<Actor*> Actors;
	HWND MainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(200, 100);

	//화면 깜박임 막기위한 2중 버퍼
	Gdiplus::Bitmap* BackBuffer = nullptr;                //빈 종이
	Gdiplus::Graphics* BackBufferGraphics = nullptr;      //그릴 도구

	Player* MainPlayer = nullptr;
};

