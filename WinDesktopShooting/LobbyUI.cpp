#include "LobbyUI.h"
#include "GameManager.h"
#include "ResourceManager.h"

LobbyUI::~LobbyUI()
{
}

void LobbyUI::HandleKeyState(IN WPARAM Key, IN bool IsPressed)
{
	if (Key == VK_UP || Key == VK_DOWN)
	{
		//키 음..
		//메뉴를 어찌하나
		if (SelectedMenu < 3 && Key == VK_DOWN && IsPressed)
			SelectedMenu++;

		if (SelectedMenu > 1 && Key == VK_UP && IsPressed)
			SelectedMenu--;

	}

	if (Key == VK_RETURN && IsPressed && IsInitialized)
	{
		GameManager::Instance().SelectLobby(static_cast<LobbyMenuType>(SelectedMenu));
	}
}

void LobbyUI::OnInitialize()
{
	Actor::OnInitialize();

	SetSize(512);
	Image = ResourceManager::Instance().GetResource(ResourceType::Logo);

	Family = new Gdiplus::FontFamily(L"Broadway");
	TextFont = new Gdiplus::Font(Family, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	TextBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255));

	anchoredPosition = { 260, 600};			// 앵커를 기준으로한 위치 설정
	anchor = { 0.0f, 0.0f };				// 앵커 포인트를 오른쪽 상단으로 설정
	Pivot = { 0.0f, 0.0f };					// 피봇 포인트를 오른쪽 상단으로 설정
	width = PixelSize * 2;
	height = PixelSize;							// 전체 너비는 4자리(0.00) * size, 높이는 size로 설정
	UpdatePosition();

	InitializeTimer = 0.0f;
}

void LobbyUI::OnTick(float deltaTime)
{

	//엔터 동시에 처리되서...
	if (!IsInitialized)
	{
		InitializeTimer += deltaTime;

		if (InitializeTimer > 1.0f)
		{
			IsInitialized = true;
		}
	}
}

void LobbyUI::OnDraw(Gdiplus::Graphics* InGraphics)
{		
	InGraphics->DrawImage(
		Image,          // 그려질 이미지
		(GameManager::Instance().ScreenWidth - Size) / 2,    // 그려질 위치
		100,
		Size, Size);

	InGraphics->DrawString(L"Start", -1, TextFont, Position, TextBrush);

	auto RecordPos = Position;
	RecordPos.Y += 40;	
	InGraphics->DrawString(L"Record", -1, TextFont, RecordPos, TextBrush);

	auto ExitPos = Position;
	ExitPos.Y += 80;
	InGraphics->DrawString(L"Exit", -1, TextFont, ExitPos, TextBrush);

	auto arrow1 = Position;
	arrow1.X -= 30;
	if (SelectedMenu == 2)
		arrow1.Y += 40;
	else if (SelectedMenu == 3)
		arrow1.Y += 80;

	InGraphics->DrawString(L"→ ", -1, TextFont, arrow1, TextBrush);

}
