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
	GameManager() = default;		//�⺻ �����ڸ� private�� �ؼ� �����Ұ�
	GameManager(const GameManager&) = delete;		//���� ������ ����
	GameManager& operator=(const GameManager&) = delete; //���� ������ ����
	GameManager(const GameManager&&) = delete;
	GameManager& operator=(const GameManager&&) = delete;		//�̵����Կ����� ����

	std::vector<Actor*> Actors;
	HWND MainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(200, 100);

	//ȭ�� ������ �������� 2�� ����
	Gdiplus::Bitmap* BackBuffer = nullptr;                //�� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;      //�׸� ����

	Player* MainPlayer = nullptr;
};

