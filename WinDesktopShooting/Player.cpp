#include "Player.h"
#include "GameManager.h"
#include "ResourceManager.h"

Player::~Player()
{
}

void Player::HandleKeyState(IN WPARAM Key, IN bool IsPressed)
{
    if (Key == VK_UP || Key == VK_DOWN || Key == VK_LEFT || Key == VK_RIGHT)
    {
        InputDirection Dir = static_cast<InputDirection>(Key);

        KeyWasPressedMap[Dir] = IsPressed;
    }
}

void Player::OnInitialize()
{
    Position.X = 300.0f;
    Position.Y = 700.0f;
    KeyWasPressedMap[InputDirection::Up] = false;
    KeyWasPressedMap[InputDirection::Down] = false;
    KeyWasPressedMap[InputDirection::Left] = false;
    KeyWasPressedMap[InputDirection::Right] = false;

    PhysicsComponent* physicsComponent = new PhysicsComponent(this, CollisionType::Circle, PhysicsLayer::Player);
    physicsComponent->SetRadius(static_cast<float>(Size * 0.5f)); // 반지름 설정
    AddComponent(physicsComponent); // 물리 컴포넌트 추가
}

void Player::OnDraw(Gdiplus::Graphics* InGraphics)
{
    Actor::OnDraw(InGraphics);

    if (!ResourceManager::Instance().GetResource(ImageType))
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            static_cast<int>(Position.X - PixelSize * Pivot.X),    // 그려질 위치
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);
    }
}

void Player::OnTick(double InDeltaTime)
{
    float moveDelta = PlayerSpeed * InDeltaTime;
    if (KeyWasPressedMap[InputDirection::Left])
    {
        Position.X -= moveDelta;
    }
    
    if (KeyWasPressedMap[InputDirection::Right])
    {
        Position.X += moveDelta;
    }

    if (Position.X <= PixelSize * Pivot.X)
        Position.X = GameManager::Instance().ScreenWidth - PixelSize * Pivot.X;
    else if (Position.X >= GameManager::Instance().ScreenWidth - PixelSize * Pivot.X)
        Position.X = PixelSize * Pivot.X;

}

void Player::OnOverlap(Actor* InOther)
{
    OutputDebugString(L"Player::OnOverlap called\n");
    if (InOther && InOther != this)
    {
        // 게임 오버 처리
        GameManager::Instance().SetGameState(GameState::GameOver);
    }
}
