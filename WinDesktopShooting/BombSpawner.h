#pragma once
#include "Actor.h"
class BombSpawner :
    public Actor
{
    public:
	BombSpawner() = delete;
	BombSpawner(ResourceType InType) : Actor(InType) {};

	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;

private:
	float initialDelay = 1.0f;			// �ʱ� ��ź ���� ���� �ð�
	float spawnInterval = 1.0f;			// �ʴ� ��ź ���� ����

	bool hasInitialDelayPassed = false;	// �ʱ� ���� �ð��� �������� ����
	float timeSinceLastSpawn = 0.0f;	// ������ ��ź ���� ���� ��� �ð�
	float TotalPlayTimer = 0.0f;
};

