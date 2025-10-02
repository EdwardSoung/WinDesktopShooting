#include "TestCollisionActor.h"
#include <string>
#include <Windows.h>

void TestCollisionActor::PrintTestResult(const TestCollisionActor* InTarget)
{
	char TempOutput[256];
	if (CheckCircleToCircleCollision(this, InTarget))
	{
		sprintf_s(TempOutput, 256, "원과 원이 충돌함\n");
	}
	else
	{
		sprintf_s(TempOutput, 256, "원과 원이 충돌하지 않음\n");

	}
	OutputDebugStringA(TempOutput);

	if (CheckCircleToRectCollision(this, InTarget))
	{
		sprintf_s(TempOutput, 256, "원과 사각형이 충돌함\n");

	}
	else
	{
		sprintf_s(TempOutput, 256, "원과 사각형이 충돌하지 않음\n");

	}
	OutputDebugStringA(TempOutput);

	if (CheckRectToRectCollision(this, InTarget))
	{
		sprintf_s(TempOutput, 256, "사각형과 사각형이 충돌함\n");

	}
	else
	{
		sprintf_s(TempOutput, 256, "사각형과 사각형이 충돌하지 않음\n");

	}
	OutputDebugStringA(TempOutput);
}

bool TestCollisionActor::CheckCircleToCircleCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo)
{
	if(!InFrom || !InTo)
		return false;

	const Gdiplus::PointF& From = InFrom->Position;
	const Gdiplus::PointF& To= InTo->Position;

	float dx = To.X - From.Y;
	float dy = To.Y - From.Y;
	float squaredDistance = dx * dx + dy * dy;

	float radiusSum = InFrom->Radius + InTo->Radius;
	float squaredRadiusSum = radiusSum * radiusSum;

	return squaredDistance <= squaredRadiusSum;
}

bool TestCollisionActor::CheckCircleToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo)
{
	if(!InFrom || !InTo)
		return false;

	const Gdiplus::PointF& From = InFrom->Position;		// 사각형
	const Gdiplus::PointF& To = InTo->Position;			// 원

	float RectLeft = From.X - InFrom->Width * 0.5f;		// 사각형의 꼭지점
	float RectRight = From.X + InFrom->Width * 0.5f;
	float RectTop = From.Y - InFrom->Height * 0.5f;
	float RectBottom = From.Y + InFrom->Height * 0.5f;

	//원의 중심에서 가각형에 가장 가까운 점 찾기
	float ClosestX = To.X;
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

	return squaredDistance <= (InTo->Radius * InTo->Radius);
}

bool TestCollisionActor::CheckRectToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo)
{
	if(!InFrom || !InTo)
		return false;

	const Gdiplus::PointF& From = InFrom->Position;
	const Gdiplus::PointF& To = InTo->Position;

	float HalfWidthFrom = InFrom->Width * 0.5f;
	float HalfHeightFrom = InFrom->Height * 0.5f;
	float HalfWidthTo = InTo->Width * 0.5f;
	float HalfHeightTo = InTo->Height * 0.5f;

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


