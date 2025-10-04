#include "BombSpawner.h"
#include "Factory.h"
#include "Bomb.h"

void BombSpawner::OnInitialize()
{
    UpdatePosition(0, -20); // 화면 밖에 위치 설정. 중요한건 아님.

    timeSinceLastSpawn = 0.0f;
    hasInitialDelayPassed = false;
    TotalPlayTimer = 0.0f;
}

void BombSpawner::OnTick(float deltaTime)
{
    Actor::OnTick(deltaTime); // 부모 클래스의 OnTick 호출

    // 경과 시간 업데이트
    timeSinceLastSpawn += deltaTime;
    TotalPlayTimer += deltaTime;


    //최저 0.1, 5초마다 0.05초씩 빨라짐 음..
    float value = 1.0f - (int)(TotalPlayTimer / 5.0f) * 0.05f;
    spawnInterval = value > 0.1f ? value : 0.1f;
    // 초기 지연 시간이 지났는지 확인
    if (!hasInitialDelayPassed)
    {
        if (timeSinceLastSpawn > initialDelay)
        {
            hasInitialDelayPassed = true;
            timeSinceLastSpawn = 0.0f; // 타이머 리셋
        }
        return; // 초기 지연 시간이 지나지 않았으면 여기서 종료
    }


    // 초기 지연 시간이 지난 후의 폭탄 생성 로직
    if (timeSinceLastSpawn > spawnInterval)
    {
        // 폭탄 생성
        Bomb* newBomb = Factory::Instance().SpawnActor<Bomb>(ResourceType::Bomb, RenderLayer::Bomb);

        // 타이머 리셋 (다음 스폰 간격을 위해)
        timeSinceLastSpawn -= spawnInterval;
    }
}