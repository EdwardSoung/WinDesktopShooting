#pragma once
#include "framework.h"
#include "Enums.h"
#include "Actor.h"
#include <unordered_map>

class Player : public Actor
{
public:
	Player() = delete;
	Player(RenderLayer InLayer) : Actor(InLayer, ResourceType::Player)
	{
		InitPosition();
	}
	virtual ~Player();

	void HandleKeyState(IN WPARAM Key, IN bool IsPressed);
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(double InDeltaTime) override;
	virtual void InitPosition() override;

private:
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
	float PlayerSpeed = 100.0f;

};

