#include "RecordUI.h"
#include "GameManager.h"
#include "ResourceManager.h"
void RecordUI::OnInitialize()
{
	SetSize(GameManager::ActorDefaultSize / 2);	// ũ�� ����
	anchoredPosition = { 30, 300 };			// ��Ŀ�� ���������� ��ġ ����
	anchor = { 0.5f, 0.0f };				// ��Ŀ ����Ʈ�� ������ ������� ����
	Pivot = { 1.0f, 0.0f };					// �Ǻ� ����Ʈ�� ������ ������� ����
	width = Size * 4;
	height = Size;							// ��ü �ʺ�� 4�ڸ�(0.00) * size, ���̴� size�� ����
	UpdatePosition();

	YPositions.clear();
	YPositions.push_back(Position.Y);
	YPositions.push_back(Position.Y + 40);
	YPositions.push_back(Position.Y + 80);

	Family = new Gdiplus::FontFamily(L"Broadway");
	TextFont = new Gdiplus::Font(Family, 30, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	DescFont = new Gdiplus::Font(Family, 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	TextBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255));

	Digits.reserve(3);			// �ּ� 3�� �ڸ� ���ڸ� ������ �� �ֵ��� ���� ����(0.00)
	digitImages.reserve(10);	// 0���� 9������ ���� �̹��� ����
	// 0���� 9������ ���� �̹��� �ε�
	for (int i = 0; i < 10; ++i)
	{
		digitImages.push_back(ResourceManager::Instance().GetResource(static_cast<ResourceType>(static_cast<int>(ResourceType::Number0) + i)));
	}
	dotImage = ResourceManager::Instance().GetResource(ResourceType::Dot); // �Ҽ��� �̹��� �ε�

	IsInitialized = false;
	InitializeTimer = 0.0f;
}
void RecordUI::HandleKeyState(IN WPARAM Key, IN bool IsPressed)
{
	if (Key == VK_RETURN && IsPressed && IsInitialized)
	{
		GameManager::Instance().ReturnToLobby();
	}
}

void RecordUI::OnTick(float deltaTime)
{	
	if (!IsInitialized)
	{
		InitializeTimer += deltaTime;

		if (InitializeTimer > 0.5f)
			IsInitialized = true;
	}
}

void RecordUI::OnDraw(Gdiplus::Graphics* InGraphics)
{
	if (!InGraphics) return;
	
	int index = 0;
	for (auto digits : Digits)
	{
		int digitCount = static_cast<int>(digits.size()) + 2;
		int indexOffset = digitCount;

		for (int i = 0; i < digitCount - 2; ++i)
		{
			if (i == 2)
			{
				// �Ҽ��� �׸���
				InGraphics->DrawImage(dotImage, static_cast<int>(Position.X) + indexOffset * Size, YPositions[index], Size, Size);
				indexOffset--;
			}

			RenderDigit(InGraphics, digits[i], indexOffset, index); // �� �ڸ� ���� ������. digits���� �ڸ����� ������ ����Ǿ� �����Ƿ�, ���� ���� �ڸ����� ������
			indexOffset--;
		}

		Gdiplus::PointF newPos = Gdiplus::PointF(Position.X - 1 * Size, YPositions[index]);
		InGraphics->DrawString(GetRankText(index), -1, TextFont, newPos, TextBrush);
		indexOffset--;		
		index++;
	}

	InGraphics->DrawString(L"Press enter to exit", -1, DescFont, Gdiplus::PointF(Position.X, Position.Y + 160), TextBrush);
	
}

void RecordUI::SetNumber(std::set<float> numbers)
{
	Digits.clear();
	for (auto iter = numbers.rbegin(); iter != numbers.rend(); ++iter) 
	{
		targetNumber = *iter; // ��ǥ ���� ������Ʈ
		std::vector<int> digits;
		int number = static_cast<int>(targetNumber * 100.0f); // �Ҽ��� ��° �ڸ����� ���. �� �Ʒ��� ���� ó��
		do
		{
			digits.push_back(number % 10);	// ���� �ڸ� ���ڸ� �߰�
			number /= 10;					// ���� �ڸ��� �̵�
		} while (number > 0);	// ��� �ڸ� ���ڸ� ó���� ������ �ݺ�(targetNumber�� ���ۺ��� 0�� ��츦 ����� do-while���)

		// �ּ� 0.00����� �Ǿ�� �Ѵ�.
		const int minimumDigits = 3; // �ּ� 3�ڸ� ����(0.00) ����
		int paddingCount = minimumDigits - (int)digits.size();
		for (int i = 0; i < paddingCount; ++i)
		{
			digits.push_back(0);	// ������ �ڸ����� 0���� ä��
		}

		SetWidth(Size * (static_cast<int>(digits.size()) + 1)); // �ʺ�� size * (�ڸ��� + �Ҽ��� �ڸ�)

		Digits.push_back(digits);
	}
}

void RecordUI::RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index, int posIndex)
{
	if (digit < 0 || digit > 9)
	{
		return; // ��ȿ���� ���� �ε����� ���� ó��
	}

	// �Ǻ��� ���� ������� ����
	graphics->DrawImage(digitImages[digit], static_cast<int>(Position.X) + index * Size, YPositions[posIndex], Size, Size);
}

const WCHAR* RecordUI::GetRankText(int index)
{
	switch (index)
	{
	default:
		return L"";
	case 0:
		return L"1st :";
	case 1:
		return L"2nd :";
	case 2:
		return L"3rd :";
	}
}
