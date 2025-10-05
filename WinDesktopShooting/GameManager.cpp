#include "GameManager.h"
#include "Factory.h"
#include "TestGridActor.h"
#include "BombSpawner.h"
#include "PhysicsComponent.h"
#include "Shield.h"

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
    
    //�켱�� �ƿ� ����ȭ��...
    //Start
    //Record(1~3)? -> ������ ��..�켱 ���� ��������
    //Exit

    //Ű �Է�..
    //��...�޾Ƽ� �ٽ� �׷��ְ� �ؾ��ϴµ�..�޴��� ������
    //�ؽ�Ʈ�� �̹����ε�... 

    MainPlayer = Factory::Instance().SpawnActor<Player>(ResourceType::Player, RenderLayer::Player);

    BG = Factory::Instance().SpawnActor<Background>(ResourceType::Background, RenderLayer::Background);
    //TestGrid = Factory::Instance().SpawnActor<TestGridActor>(ResourceType::Test, RenderLayer::Test);
    Spawner = Factory::Instance().SpawnActor<BombSpawner>(ResourceType::None);
    Timer = Factory::Instance().SpawnActor<TimerUI>(ResourceType::None, RenderLayer::UI);
    //Factory::Instance().SpawnActor<Shield>(ResourceType::Shield3, RenderLayer::Player);
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
        ProcessPendingDestroyAtors();
    }
    
    if (State == GameState::GameOver)
    {
        RequestDestroy(Spawner);
        RequestDestroy(MainPlayer);
        MainPlayer = nullptr;
        RequestDestroy(Timer);
        Lobby = Factory::Instance().SpawnActor<LobbyUI>(ResourceType::None, RenderLayer::UI);
        SetGameState(GameState::Lobby);
    }

    if (State == GameState::Lobby)
    {
        for (auto ActorData : Actors)
        {
            for (auto actor : ActorData.second)
            {
                actor->OnTick(InDeltaTime);
            }
        }

        ProcessPendingDestroyAtors();
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
}

void GameManager::ProcessPendingDestroyAtors()
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

