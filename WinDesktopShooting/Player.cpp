#include "Player.h"

Player::Player(IN Gdiplus::Point Size, IN const WCHAR* Path)
{
    ScreenSize = Size;
    Image = new Gdiplus::Bitmap(Path);
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        //플레이어 이미지 정상 로딩 실패
        delete Image;
        Image = nullptr;
        //MessageBox(hWnd, L"플레이어 이미지 로드 실패", L"Error", MB_OK | MB_ICONERROR);
    }

    InitPosition();
}

Player::~Player()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Player::HandleKeyState(IN WPARAM Key, IN bool IsPressed)
{
    if (Key == VK_UP || Key == VK_DOWN || Key == VK_LEFT || Key == VK_RIGHT)
    {
        InputDirection Dir = static_cast<InputDirection>(Key);

        if (IsPressed)
            Move(Dir);

        //if(IsPressed && !KeyWasPressedMap[Dir])
            //Move(Dir);        
        //KeyWasPressedMap[Dir] = IsPressed;
    }
}

void Player::Draw(Gdiplus::Graphics* g_Graphics)
{
    g_Graphics->DrawImage(Image, 
        static_cast<int>(Position.X - PlayerPixelSize * Pivot.X),
        static_cast<int>(Position.Y - PlayerPixelSize * Pivot.Y),
        PlayerPixelSize, PlayerPixelSize);
}

void Player::Move(InputDirection InDirection)
{
    switch (InDirection)
    {
    case InputDirection::Left:
        if (Position.X <= PlayerPixelSize / 2)
            Position.X = ScreenSize.X - PlayerPixelSize * Pivot.X;
        else
            Position.X -= PlayerSpeed;
      
        break;
    case InputDirection::Right:
        if (Position.X >= ScreenSize.X - PlayerPixelSize * Pivot.X)
            Position.X = PlayerPixelSize * Pivot.X;
        else
            Position.X += PlayerSpeed;
        break;
    }
}

void Player::InitPosition()
{
    Position.X = ScreenSize.X / 2;
    Position.Y = 700;// ScreenSize.Y - PlayerPixelSize;
}
