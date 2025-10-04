#include "Bomb.h"
#include "GameManager.h"
#include "PhysicsComponent.h"

void Bomb::OnInitialize()
{
	dropSpeed = 0.0f; // �ʱ� ��� �ӵ� ����

	SetSize(GameManager::ActorDefaultSize / 2); // ũ�� ����

	float HalfSize = Size * 0.5f;
	Position.X = static_cast<float>(HalfSize + rand() % (GameManager::ScreenWidth - Size)); // ���� X ��ġ ����
	Position.Y = static_cast<float>(-Size); // ȭ�� ���ʿ��� ����

	Angle = 180.0f;	// ȸ�� ����

	PhysicsComponent* physicsComponent = new PhysicsComponent(this, CollisionType::Rectangle, PhysicsLayer::Bomb);
	physicsComponent->SetWidth(static_cast<float>(HalfSize));
	physicsComponent->SetHeight(HalfSize * 0.75f);
	AddComponent(physicsComponent); // ���� ������Ʈ �߰�
}

//�߷°��ӵ�..?
float m = 10;
float g = 9.81f;
void Bomb::OnTick(float deltaTime)
{
	Actor::OnTick(deltaTime); // �θ� Ŭ������ OnTick ȣ��

	dropSpeed += m * g * deltaTime; // ��� �ӵ� ������Ʈ

	Position.Y += dropSpeed * deltaTime; // Y ��ġ ������Ʈ

	lifetime -= deltaTime; // ���� ����

	// ȭ�� ������ �����ų� ������ �� �� ��� ���� ����
	if (Position.Y > GameManager::ScreenHeight + Size || lifetime < 0.0f)
	{
		DestroyActor();
	}
}

void Bomb::OnOverlap(Actor* other)
{
	if (other && other != this)
	{
		// ��ź�� �ٸ� ���Ͱ� ��ĥ �� ó��
		// ��: ��ź�� �÷��̾�� ��ġ�� �÷��̾�� ���ظ� �ְų� ���� ���� ó��
		OutputDebugString(L"Bomb::OnOverlap called\n");

		// ��ź ����
		DestroyActor();
	}
}

