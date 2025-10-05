#pragma once
#include "UserInterface.h"

class LobbyUI :
    public UserInterface
{
public:
	LobbyUI() = delete;
	LobbyUI(ResourceType InType) : UserInterface(InType) {};

	//virtual void OnInitialize() override;
	//virtual void OnTick(float deltaTime) override;
	//virtual void OnDraw(Gdiplus::Graphics* graphics) override;
};

