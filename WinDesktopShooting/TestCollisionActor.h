#pragma once
#include "Actor.h"
#include "Enums.h"

class TestCollisionActor :
    public Actor
{
public:
    TestCollisionActor() = delete;
    TestCollisionActor(ResourceType InType) : Actor(InType) {}

    float Radius = 25.0f;

    float Width = 50.00f;
    float Height = 50.0f;

    void PrintTestResult(const TestCollisionActor* InTarget);

private:
    bool CheckCircleToCircleCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo);
    bool CheckCircleToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo);
    bool CheckRectToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo);
};

