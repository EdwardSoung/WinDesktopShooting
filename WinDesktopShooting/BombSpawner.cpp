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
    Actor::OnTick(deltaTime); // �θ� Ŭ������ OnTick ȣ��

    // ��� �ð� ������Ʈ
    timeSinceLastSpawn += deltaTime;
    TotalPlayTimer += deltaTime;


    //���� 0.1, 5�ʸ��� 0.05�ʾ� ������ ��..
    float value = 1.0f - (int)(TotalPlayTimer / 5.0f) * 0.05f;
    spawnInterval = value > 0.1f ? value : 0.1f;
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
        // ��ź ����
        Bomb* newBomb = Factory::Instance().SpawnActor<Bomb>(ResourceType::Bomb, RenderLayer::Bomb);

        // Ÿ�̸� ���� (���� ���� ������ ����)
        timeSinceLastSpawn -= spawnInterval;
    }
}