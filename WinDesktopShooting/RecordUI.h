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


	float targetNumber = 0.0f;	// ��ǥ ����
	std::vector<int> digits;	// �� �ڸ� ���ڸ� �����ϴ� ����(0.0�� �� �־�� �ϹǷ� �ּ� 2�� �ڸ��� ����)
	std::vector<Gdiplus::Bitmap*> digitImages;	// �� �ڸ� ���� �̹���
	Gdiplus::Bitmap* dotImage = nullptr;		// �Ҽ��� �̹���

	int SelectedMenu = 0;
	bool IsInitialized = false;
	float InitializeTimer = 0.0f;

};

