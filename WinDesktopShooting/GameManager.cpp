#include "GameManager.h"

void GameManager::Initialize()
{
	BackBuffer = new Gdiplus::Bitmap(ScreenWidth, ScreenHeight, PixelFormat32bppARGB);
	BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
	if (!BackBufferGraphics)
	{
		//안만들어졌으면 에러 출력
		MessageBox(MainWindow, L"Back Buffer Graphics Gnenarate failed!", L"Error", MB_OK | MB_ICONERROR);
	}
    Actors.push_back(new Background(L"./Images/BG.png"));
    Actors.push_back(new TestGridActor());
    //Actors.push_back(new TestHouseActor());
    MainPlayer = new Player(L"./Images/Airplane01.png");
    Actors.push_back(MainPlayer);
}

void GameManager::Destroy()
{
    for (Actor* ActorData : Actors)
    {
        delete ActorData;
        ActorData = nullptr;
    }

    Actors.clear();

    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
	for (Actor* ActorData : Actors)
	{
		ActorData->OnTick(InDeltaTime);
	}
}

void GameManager::Draw(HDC InHdc)
{
    if (BackBufferGraphics)
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        for (Actor* ActorData : Actors)
        {
            ActorData->OnDraw(BackBufferGraphics);
        }

    }

	Gdiplus::Graphics GraphicsInstance(InHdc);
	GraphicsInstance.DrawImage(BackBuffer, 0, 0);
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}
