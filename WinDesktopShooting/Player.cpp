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

void Player::OnDraw(Gdiplus::Graphics* InGraphics)
{
    Actor::OnDraw(InGraphics);

    if (!Singleton<ResourceManager>::Instance().GetResource(ImageType))
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
        Position.X = Singleton<GameManager>::Instance().ScreenWidth - PixelSize * Pivot.X;
    else if (Position.X >= Singleton<GameManager>::Instance().ScreenWidth - PixelSize * Pivot.X)
        Position.X = PixelSize * Pivot.X;

}



void Player::InitPosition()
{
    Position.X = 300.0f;
    Position.Y = 700.0f;
}
