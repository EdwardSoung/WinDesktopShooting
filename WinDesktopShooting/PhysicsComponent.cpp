#include "PhysicsComponent.h"
#include "Actor.h"

void PhysicsComponent::OnTick(double InDeltaTime)
{
}

bool PhysicsComponent::IsCollision(PhysicsComponent* InOther) const
{
	bool Result = false;

	if (!InOther || InOther == this)
		return Result;

	if (this->GetLayer() == PhysicsLayer::None || InOther->GetLayer() == PhysicsLayer::None)
		return Result;

	if (Collision == InOther->GetCollisionType())
	{
		switch (Collision)
		{
		case CollisionType::Circle:
			Result = CheckCircleToCircleCollision(this, InOther);
			break;
		case CollisionType::Rectangle:
			Result = CheckRectToRectCollision(this, InOther);
			break;
		}
	}
	else
	{
		Result = CheckCircleToRectCollision(this, InOther);
	}

	return Result;
}

bool PhysicsComponent::CheckCircleToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)
		return false;

	const Gdiplus::PointF& From = InFrom->GetOwner()->GetPosition();
	const Gdiplus::PointF& To = InTo->GetOwner()->GetPosition();

	float dx = To.X - From.Y;
	float dy = To.Y - From.Y;
	float squaredDistance = dx * dx + dy * dy;

	float radiusSum = InFrom->GetRadius() + InTo->GetRadius();
	float squaredRadiusSum = radiusSum * radiusSum;

	return squaredDistance <= squaredRadiusSum;
}

bool PhysicsComponent::CheckCircleToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)
		return false;

	const PhysicsComponent* Circle;
	const PhysicsComponent* Rect;

	if (InFrom->GetCollisionType() == CollisionType::Circle)
	{
		Circle = InFrom;
		Rect = InTo;
	}
	else
	{
		Circle = InTo;
		Rect = InFrom;
	}

	const Gdiplus::PointF& From = Rect->GetOwner()->GetPosition();		// 사각형
	const Gdiplus::PointF& To = Circle->GetOwner()->GetPosition();			// 원

	float RectLeft = From.X - Rect->GetWidth() * 0.5f;		// 사각형의 꼭지점
	float RectRight = From.X + Rect->GetWidth() * 0.5f;
	float RectTop = From.Y - Rect->GetHeight() * 0.5f;
	float RectBottom = From.Y + Rect->GetHeight() * 0.5f;

	//원의 중심에서 가각형에 가장 가까운 점 찾기
	float ClosestX = From.X;
	float ClosestY = To.Y;

	if (To.X < RectLeft)
		ClosestX = RectLeft;
	else if (To.X > RectRight)
		ClosestX = RectRight;

	if (To.Y < RectTop)
		ClosestY = RectTop;
	else if (To.Y > RectBottom)
		ClosestY = RectBottom;

	float dx = To.X - ClosestX;
	float dy = To.Y - ClosestY;
	float squaredDistance = dx * dx + dy * dy;

	return squaredDistance <= (Circle->GetRadius() * Circle->GetRadius());
}

bool PhysicsComponent::CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)
		return false;

	const Gdiplus::PointF& From = InFrom->GetOwner()->GetPosition();
	const Gdiplus::PointF& To = InTo->GetOwner()->GetPosition();

	float HalfWidthFrom = InFrom->GetWidth() * 0.5f;
	float HalfHeightFrom = InFrom->GetHeight() * 0.5f;
	float HalfWidthTo = InTo->GetWidth() * 0.5f;
	float HalfHeightTo = InTo->GetHeight() * 0.5f;

	float fromLeft = From.X - HalfWidthFrom;
	float fromRight = From.X + HalfWidthFrom;
	float fromTop = From.Y - HalfHeightFrom;
	float fromBottom = From.Y + HalfHeightFrom;

	float toLeft = To.X - HalfWidthTo;
	float toRight = To.X + HalfWidthTo;
	float toTop = To.Y - HalfHeightTo;
	float toBottom = To.Y - HalfHeightTo;

	return (fromRight >= toLeft && fromLeft <= toRight && fromBottom >= toTop && fromTop <= toBottom);
}
