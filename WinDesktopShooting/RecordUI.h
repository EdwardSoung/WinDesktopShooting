#pragma once
#include "UserInterface.h"
#include <set>
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

	void SetNumber(std::set<float> numbers);
private:
	void RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index, int posIndex);
	const WCHAR* GetRankText(int index);

	Gdiplus::FontFamily* Family = nullptr;
	Gdiplus::Font* TextFont = nullptr;
	Gdiplus::Font* DescFont = nullptr;
	Gdiplus::SolidBrush* TextBrush = nullptr;

	float targetNumber = 0.0f;	// ��ǥ ����
	std::vector<std::vector<int>> Digits;
	std::vector<Gdiplus::Bitmap*> digitImages;	// �� �ڸ� ���� �̹���
	Gdiplus::Bitmap* dotImage = nullptr;		// �Ҽ��� �̹���

	std::vector<int> YPositions;

	int SelectedMenu = 0;
	bool IsInitialized = false;
	float InitializeTimer = 0.0f;

};

