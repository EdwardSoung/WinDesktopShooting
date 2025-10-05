#pragma once
#include "framework.h"
#include "Enums.h"
#include "Actor.h"
#include <unordered_map>

class Player : public Actor
{
public:
	Player() = delete;
	Player(ResourceType InType) : Actor(InType)
	{
	}
	virtual ~Player();

	void HandleKeyState(IN WPARAM Key, IN bool IsPressed);
	virtual void OnInitialize() override;
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(float InDeltaTime) override;
	virtual void OnOverlap(Actor* InOther) override;

private:
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
	float PlayerSpeed = 150.0f;

};

