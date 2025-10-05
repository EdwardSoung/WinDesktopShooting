#include "LobbyUI.h"
#include "GameManager.h"

LobbyUI::~LobbyUI()
{
}

void LobbyUI::HandleKeyState(IN WPARAM Key, IN bool IsPressed)
{
	if (Key == VK_UP || Key == VK_DOWN)
	{
		//Ű ��..
		//�޴��� �����ϳ�
		if (SelectedMenu < 3 && Key == VK_DOWN && IsPressed)
			SelectedMenu++;

		if (SelectedMenu > 1 && Key == VK_UP && IsPressed)
			SelectedMenu--;

	}

	if (Key == VK_RETURN)
	{
		GameManager::Instance().SelectLobby(static_cast<LobbyMenuType>(SelectedMenu));
	}
}

void LobbyUI::OnInitialize()
{
	Actor::OnInitialize();

	Family = new Gdiplus::FontFamily(L"Arial");
	TextFont = new Gdiplus::Font(Family, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	TextBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255));

	anchoredPosition = { 260, 600};			// ��Ŀ�� ���������� ��ġ ����
	anchor = { 0.0f, 0.0f };				// ��Ŀ ����Ʈ�� ������ ������� ����
	Pivot = { 0.0f, 0.0f };					// �Ǻ� ����Ʈ�� ������ ������� ����
	width = Size * 2;
	height = Size;							// ��ü �ʺ�� 4�ڸ�(0.00) * size, ���̴� size�� ����
	UpdatePosition();
}

void LobbyUI::OnTick(float deltaTime)
{
}

void LobbyUI::OnDraw(Gdiplus::Graphics* InGraphics)
{		
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

	InGraphics->DrawString(L"�� ", -1, TextFont, arrow1, TextBrush);

}
