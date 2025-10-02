#pragma once
#include "Component.h"
#include "Enums.h"
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Actor* InOwner, CollisionType InType = CollisionType::Circle, PhysicsLayer InLayer = PhysicsLayer::None)
		:Component(InOwner), Collision(InType), Layer(InLayer)
	{
	}

	virtual void OnTick(double InDeltaTime) override;

	bool IsCollision(PhysicsComponent* InOther) const;

	inline float GetRadius() const { return Data1; }
	inline float GetWidth() const { return Data1; }
	inline float GetHeight() const { return Data2; }
	inline CollisionType GetCollisionType() const { return Collision; }
	inline PhysicsLayer GetLayer() const { return Layer; }

	inline void SetRadius(float InRadius) { Data1 = InRadius; }
	inline void SetWidth(float InWidth) { Data1 = InWidth; }
	inline void SetHeight(float InHeight) { Data1 = InHeight; }

private:
	static bool CheckCircleToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckCircleToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);

	CollisionType Collision = CollisionType::Circle;
	PhysicsLayer Layer = PhysicsLayer::None;

	//원이면 1만, 사각형이면 둘다 쓰려는 형태. Getter로
	float Data1 = 0.0f;
	float Data2 = 0.0f;
};

