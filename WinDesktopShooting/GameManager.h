#pragma once
#include <map>
#include <set>
#include "framework.h"
#include "Actor.h"
#include "Player.h"
#include "Background.h"
#include "TestGridActor.h"
#include "TestHouseActor.h"
#include "Singleton.h"
#include "PhysicsComponent.h"
#include "BombSpawner.h"
#include "TimerUI.h"
#include "Shield.h"
#include "LobbyUI.h"

class GameManager : public Singleton<GameManager>
{
	//friend : �ٸ� Ŭ������ �ڽ��� private/protected �׸� ���� ���
	//friend : ���� Ŭ������ �� Ŭ������ ����
	friend class Singleton<GameManager>;
public:

	virtual void Initialize() override;
	virtual void OnDestroy() override;

	void Tick(float InDeltaTime);
	void Draw(HDC InHdc);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);
	void RegistActor(RenderLayer InLayer, Actor* InActor);

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

	inline Gdiplus::PointF GetPlayerPosition() { return MainPlayer->GetPosition(); }
	inline Gdiplus::Point GetAppPosition() { return AppPosition; }
	inline void RequestDestroy(Actor* DestroyTarget) { PendingDestroyActors.insert(DestroyTarget); }
	inline void SetGameState(GameState InState) { State = InState; }

private:
	GameManager() = default;
	virtual ~GameManager() = default;

	void ProcessPendingDestroyAtors();
	void UnRegistActor(Actor* InActor);

	void ProcessCollisions();					// �浹 ó�� �Լ�
	void ProcessPendingDestroyActors();			// ���� ������ ���͵��� ������ �����ϴ� �Լ�

	std::map<RenderLayer, std::set<Actor*>> Actors;
	HWND MainWindow = nullptr;
	Gdiplus::Point AppPosition = Gdiplus::Point(200, 100);
	std::set<Actor*> PendingDestroyActors;
	std::map<PhysicsLayer, std::vector<PhysicsComponent*>> PhysicsComponents; // ���� ������Ʈ ����Ʈ

	//ȭ�� ������ �������� 2�� ����
	Gdiplus::Bitmap* BackBuffer = nullptr;                //�� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;      //�׸� ����

	Player* MainPlayer = nullptr;
	TestGridActor* TestGrid = nullptr;

	BombSpawner* Spawner = nullptr;
	TimerUI* Timer = nullptr;
	Background* BG = nullptr;
	

	GameState State = GameState::Playing;
};
 