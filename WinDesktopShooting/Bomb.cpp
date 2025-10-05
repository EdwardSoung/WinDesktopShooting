#include "Bomb.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "PhysicsComponent.h"

void Bomb::OnInitialize()
{
	dropSpeed = 0.0f; // �ʱ� ��� �ӵ� ����

	Image = ResourceManager::Instance().GetResource(ImageType);
	//����� ����...

	Mass = GetMetorSize();
	SetSize(Mass); // ũ�� ����

	float HalfSize = Size * 0.5f;
	Position.X = static_cast<float>(HalfSize + rand() % (GameManager::ScreenWidth - Size)); // ���� X ��ġ ����
	Position.Y = static_cast<float>(-Size); // ȭ�� ���ʿ��� ����

	//Angle = 180.0f;	// ȸ�� ����

	PhysicsComponent* physicsComponent = new PhysicsComponent(this, CollisionType::Circle, PhysicsLayer::Bomb);
	physicsComponent->SetRadius(HalfSize);
	AddComponent(physicsComponent); // ���� ������Ʈ �߰�
}

void Bomb::OnTick(float deltaTime)
{
	//��� ȸ��
	Angle += 1.0f;

	dropSpeed += (Mass * 0.5f) * g * deltaTime; // ��� �ӵ� ������Ʈ

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

int Bomb::GetMetorSize()
{
	switch(ImageType)
	{
	case ResourceType::Meteor1:
		return 15;
	case ResourceType::Meteor2:
		return 18;
	case ResourceType::Meteor3:
		return 28;
	case ResourceType::Meteor4:
		return 43;
	case ResourceType::Meteor5:
		return 96;
	}
	return 0;
}

