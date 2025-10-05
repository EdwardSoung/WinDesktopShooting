#pragma once
#include "UserInterface.h"
#include <Windows.h>

class LobbyUI :
    public UserInterface
{
public:
	LobbyUI() = delete;
	LobbyUI(ResourceType InType) : UserInterface(InType) {};
	virtual ~LobbyUI();

	void HandleKeyState(IN WPARAM Key, IN bool IsPressed);
	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	
private:
	int SelectedMenu = 1;
	Gdiplus::FontFamily* Family;
	Gdiplus::Font* TextFont;
	Gdiplus::SolidBrush* TextBrush;
};

