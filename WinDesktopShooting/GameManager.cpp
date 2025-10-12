#include "GameManager.h"
#include "Factory.h"
#include "TestGridActor.h"
#include "BombSpawner.h"
#include "PhysicsComponent.h"
#include "Shield.h"
#include "WinDesktopShooting.h"

#include<algorithm>

void GameManager::Initialize()
{
	BackBuffer = new Gdiplus::Bitmap(ScreenWidth, ScreenHeight, PixelFormat32bppARGB);
	BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
	if (!BackBufferGraphics)
	{
		//�ȸ���������� ���� ���
		MessageBox(MainWindow, L"Back Buffer Graphics Gnenarate failed!", L"Error", MB_OK | MB_ICONERROR);
	}

    BG = Factory::Instance().SpawnActor<Background>(ResourceType::Background, RenderLayer::Background);
    Lobby = Factory::Instance().SpawnActor<LobbyUI>(ResourceType::None, RenderLayer::UI);
    SetGameState(GameState::Lobby);
}

void GameManager::OnDestroy()
{
    for (auto ActorData : Actors)
    {
        for (auto actor : ActorData.second)
        {
            delete actor;
        }
    }
    PhysicsComponents.clear();
    Actors.clear();

    delete BackBuffer;
    BackBuffer = nullptr;

    BG = nullptr;
    Spawner = nullptr;
    MainPlayer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    if (State == GameState::Playing)
    {
        for (auto ActorData : Actors)
        {
            for (auto actor : ActorData.second)
            {
                actor->OnTick(InDeltaTime);
            }
        }

        ProcessCollisions();
        ProcessPendingDestroyActors();
    }
    else if (State == GameState::GameOver)
    {
        SaveRecord();

        RequestDestroy(Spawner);
        RequestDestroy(MainPlayer);
        RequestDestroy(Timer);

        ProcessPendingDestroyActors();
        Spawner = nullptr;
        MainPlayer = nullptr;
        Timer = nullptr;

        Lobby = Factory::Instance().SpawnActor<LobbyUI>(ResourceType::None, RenderLayer::UI);
        SetGameState(GameState::Lobby);
    }
    else if (State == GameState::Lobby)
    {
        for (auto ActorData : Actors)
        {
            for (auto actor : ActorData.second)
            {
                actor->OnTick(InDeltaTime);
            } 
        }
    }
    else if (State == GameState::Record)
    {
        for (auto ActorData : Actors)
        {
            for (auto actor : ActorData.second)
            {
                actor->OnTick(InDeltaTime);
            } 
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
    if(MainPlayer)
        MainPlayer->HandleKeyState(InKey, InIsPressed);

    if (Record)
        Record->HandleKeyState(InKey, InIsPressed);
        
    if (Lobby)
        Lobby->HandleKeyState(InKey, InIsPressed);

    if (TestGrid)
    {
        TestGrid->DestroyActor();
        TestGrid = nullptr;
    }
}

void GameManager::RegistActor(RenderLayer InLayer, Actor* InActor)
{
    if (InActor)
    {
        Actors[InLayer].insert(InActor);
        PhysicsComponent* physicsComponent = InActor->GetComponent<PhysicsComponent>();
        if (physicsComponent && physicsComponent->GetLayer() != PhysicsLayer::None)
        {
            PhysicsComponents[physicsComponent->GetLayer()].push_back(physicsComponent);
        }
    }
}

void GameManager::SelectLobby(LobbyMenuType InMenu)
{
    LobbyMenuType menu = InMenu;
    
    RequestDestroy(Lobby);
    ProcessPendingDestroyActors();
    Lobby = nullptr;
    if (menu == LobbyMenuType::Start)
    {
		MainPlayer = Factory::Instance().SpawnActor<Player>(ResourceType::Player, RenderLayer::Player);
		Spawner = Factory::Instance().SpawnActor<BombSpawner>(ResourceType::None);
		Timer = Factory::Instance().SpawnActor<TimerUI>(ResourceType::None, RenderLayer::UI);
        SetGameState(GameState::Playing);
    }
    else if (menu == LobbyMenuType::Record)
    {
        Record = Factory::Instance().SpawnActor<RecordUI>(ResourceType::None, RenderLayer::UI);
        Record->SetNumber(RecordData);
        SetGameState(GameState::Record);
    }
    else
    {
        DestroyWindow(MainWindow);
    }
}

void GameManager::ReturnToLobby()
{
    RequestDestroy(Record);
    ProcessPendingDestroyActors();
    Record = nullptr;
    Lobby = Factory::Instance().SpawnActor<LobbyUI>(ResourceType::None, RenderLayer::UI);
    SetGameState(GameState::Lobby);
}

void GameManager::ProcessPendingDestroyActors()
{
    for (Actor* actor : PendingDestroyActors)
    {
        if (actor)
        {   
            UnRegistActor(actor);
            actor->OnDestroy();
            delete actor;
        }
    }

    PendingDestroyActors.clear();
}

void GameManager::SaveRecord()
{
    if (Timer && Timer->GetElapsedTime() > 0.0f)
    {
        if (RecordData.size() < 3)
            RecordData.insert(Timer->GetElapsedTime());
        else
        {
            for (auto record = RecordData.rbegin(); record != RecordData.rend(); record++)
            {
                if (Timer->GetElapsedTime() > *record)
                {
                    //�� �տ��� ����
                    RecordData.erase(RecordData.begin());
                    RecordData.insert(Timer->GetElapsedTime());
                    break;
                }
            }
        }
    }
}

void GameManager::UnRegistActor(Actor* InActor)
{
    std::set<Actor*>& actorSet = Actors[InActor->GetLayer()];

    if (actorSet.find(InActor) != actorSet.end())
    {
        PhysicsComponent* physicsComponent = InActor->GetComponent<PhysicsComponent>();
        if (physicsComponent)
        {
            // ���� ������Ʈ ����
            auto& physicsObjects = PhysicsComponents[physicsComponent->GetLayer()];
            auto it = std::find(physicsObjects.begin(), physicsObjects.end(), physicsComponent);
            if (it != physicsObjects.end())
            {                
                std::swap(*it, physicsObjects.back());	// ������ ���� ������Ʈ�� ����
                physicsObjects.pop_back();				// ������ ���� ������Ʈ ����
            }
        }
        actorSet.erase(InActor);
    }
}

void GameManager::ProcessCollisions()
{
    PhysicsComponent* player = *(PhysicsComponents[PhysicsLayer::Player].begin());	// �÷��̾�� 1����

    // �÷��̾ ��� ��ź�� �浹�ϴ����� Ȯ��
    // Ȯ�� �� ���� �ݸ��� Ÿ�Կ� ���� ó��(���� ��, ���� �簢��, �簢���� �簢�� �� 3���� ���̽�)
    for (auto& bomb : PhysicsComponents[PhysicsLayer::Bomb])
    {
        if (player->IsCollision(bomb)) // �÷��̾�� ��ź ���� �浹 Ȯ��
        {
            // �浹 �߻� �� �÷��̾�� ��ź�� OnOverlap ȣ��
            player->GetOwner()->OnOverlap(bomb->GetOwner());
            bomb->GetOwner()->OnOverlap(player->GetOwner());
        }
    }
}


