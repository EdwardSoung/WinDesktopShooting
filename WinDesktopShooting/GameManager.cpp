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

    MainPlayer = new Player(RenderLayer::Player);
    AddActor(MainPlayer);
    AddActor(new Background(RenderLayer::Background));
    AddActor(new TestGridActor(RenderLayer::Test));
}

void GameManager::Destroy()
{
    for (auto ActorData : Actors)
    {
        for (auto actor : ActorData.second)
        {
            delete actor;
            actor = nullptr;

        }
    }

    Actors.clear();

    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    for (auto ActorData : Actors)
    {
        for (auto actor : ActorData.second)
        {
            actor->OnTick(InDeltaTime);
        }
    }
}

void GameManager::Draw(HDC InHdc)
{
    if (BackBufferGraphics)
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        for (auto ActorData : Actors)
        {
            for (auto actor : ActorData.second)
            {
                actor->OnDraw(BackBufferGraphics);
            }
        }

    }

	Gdiplus::Graphics GraphicsInstance(InHdc);
	GraphicsInstance.DrawImage(BackBuffer, 0, 0);
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}

void GameManager::AddActor(Actor* InActor)
{
    auto ActorList = &Actors[InActor->GetLayer()];
    ActorList->push_back(InActor);
}
