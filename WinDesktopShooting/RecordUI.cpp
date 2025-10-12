#include "RecordUI.h"
#include "GameManager.h"
#include "ResourceManager.h"
void RecordUI::OnInitialize()
{
	SetSize(GameManager::ActorDefaultSize / 2);	// 크기 설정
	anchoredPosition = { 30, 300 };			// 앵커를 기준으로한 위치 설정
	anchor = { 0.5f, 0.0f };				// 앵커 포인트를 오른쪽 상단으로 설정
	Pivot = { 1.0f, 0.0f };					// 피봇 포인트를 오른쪽 상단으로 설정
	width = Size * 4;
	height = Size;							// 전체 너비는 4자리(0.00) * size, 높이는 size로 설정
	UpdatePosition();

	YPositions.clear();
	YPositions.push_back(Position.Y);
	YPositions.push_back(Position.Y + 40);
	YPositions.push_back(Position.Y + 80);

	Family = new Gdiplus::FontFamily(L"Broadway");
	TextFont = new Gdiplus::Font(Family, 30, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	DescFont = new Gdiplus::Font(Family, 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	TextBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255));

	Digits.reserve(3);			// 최소 3개 자리 숫자를 저장할 수 있도록 벡터 예약(0.00)
	digitImages.reserve(10);	// 0부터 9까지의 숫자 이미지 예약
	// 0부터 9까지의 숫자 이미지 로드
	for (int i = 0; i < 10; ++i)
	{
		digitImages.push_back(ResourceManager::Instance().GetResource(static_cast<ResourceType>(static_cast<int>(ResourceType::Number0) + i)));
	}
	dotImage = ResourceManager::Instance().GetResource(ResourceType::Dot); // 소수점 이미지 로드

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
				// 소수점 그리기
				InGraphics->DrawImage(dotImage, static_cast<int>(Position.X) + indexOffset * Size, YPositions[index], Size, Size);
				indexOffset--;
			}

			RenderDigit(InGraphics, digits[i], indexOffset, index); // 각 자리 숫자 렌더링. digits에는 자리수가 역으로 저장되어 있으므로, 가장 높은 자리부터 렌더링
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
		targetNumber = *iter; // 목표 숫자 업데이트
		std::vector<int> digits;
		int number = static_cast<int>(targetNumber * 100.0f); // 소수점 둘째 자리까지 고려. 그 아래는 버림 처리
		do
		{
			digits.push_back(number % 10);	// 현재 자리 숫자를 추가
			number /= 10;					// 다음 자리로 이동
		} while (number > 0);	// 모든 자리 숫자를 처리할 때까지 반복(targetNumber가 시작부터 0인 경우를 대비해 do-while사용)

		// 최소 0.00출력이 되어야 한다.
		const int minimumDigits = 3; // 최소 3자리 숫자(0.00) 보장
		int paddingCount = minimumDigits - (int)digits.size();
		for (int i = 0; i < paddingCount; ++i)
		{
			digits.push_back(0);	// 부족한 자리수는 0으로 채움
		}

		SetWidth(Size * (static_cast<int>(digits.size()) + 1)); // 너비는 size * (자리수 + 소수점 자리)

		Digits.push_back(digits);
	}
}

void RecordUI::RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index, int posIndex)
{
	if (digit < 0 || digit > 9)
	{
		return; // 유효하지 않은 인덱스나 숫자 처리
	}

	// 피봇은 왼쪽 상단으로 설정
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
