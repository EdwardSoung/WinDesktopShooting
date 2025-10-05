#include "BombSpawner.h"
#include "Factory.h"
#include "Bomb.h"

void BombSpawner::OnInitialize()
{
    UpdatePosition(0, -20); // ȭ�� �ۿ� ��ġ ����. �߿��Ѱ� �ƴ�.

    timeSinceLastSpawn = 0.0f;
    hasInitialDelayPassed = false;
    TotalPlayTimer = 0.0f;
}

void BombSpawner::OnTick(float deltaTime)
{
    // ��� �ð� ������Ʈ
    timeSinceLastSpawn += deltaTime;
    TotalPlayTimer += deltaTime;


    //���� 0.1, 5�ʸ��� 0.05�ʾ� ������ ��..
    float value = 1.0f - (int)(TotalPlayTimer / 5.0f) * 0.1f;
    spawnInterval = value > 0.2f ? value : 0.2f;
    // �ʱ� ���� �ð��� �������� Ȯ��
    if (!hasInitialDelayPassed)
    {
        if (timeSinceLastSpawn > initialDelay)
        {
            hasInitialDelayPassed = true;
            timeSinceLastSpawn = 0.0f; // Ÿ�̸� ����
        }
        return; // �ʱ� ���� �ð��� ������ �ʾ����� ���⼭ ����
    }


    // �ʱ� ���� �ð��� ���� ���� ��ź ���� ����
    if (timeSinceLastSpawn > spawnInterval)
    {
        //�÷��� Ÿ�Ӹ��� � �����ϴµ�... Ȯ����?
        // ��ź ����
        Bomb* newBomb = Factory::Instance().SpawnActor<Bomb>(GetMeteor(), RenderLayer::Meteor);

        // Ÿ�̸� ���� (���� ���� ������ ����)
        timeSinceLastSpawn -= spawnInterval;
    }
}

ResourceType BombSpawner::GetMeteor()
{
    //5 : 5%
    //4 : 10%
    //3 : 15%
    //4 : 20%
    //5 : 50%
    int random = rand() % 10000;
    if (random < 500)
        return ResourceType::Meteor5;
    else if (random < 1500)
        return ResourceType::Meteor4;
    else if (random < 3000)
        return ResourceType::Meteor3;
    else if (random < 5000)
        return ResourceType::Meteor2;
    else
        return ResourceType::Meteor1;
}
