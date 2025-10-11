#pragma once
#include "UserInterface.h"
class RecordUI :
    public UserInterface
{
public:
	RecordUI() = delete;
	RecordUI(ResourceType InType) : UserInterface(InType) {};

	void HandleKeyState(IN WPARAM Key, IN bool IsPressed);

	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;

private:
	void SetNumber(float number);
	void RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index);


	float targetNumber = 0.0f;	// 목표 숫자
	std::vector<int> digits;	// 각 자리 숫자를 저장하는 벡터(0.0은 들어가 있어야 하므로 최소 2개 자리로 예약)
	std::vector<Gdiplus::Bitmap*> digitImages;	// 각 자리 숫자 이미지
	Gdiplus::Bitmap* dotImage = nullptr;		// 소수점 이미지

	int SelectedMenu = 0;
	bool IsInitialized = false;
	float InitializeTimer = 0.0f;

};

