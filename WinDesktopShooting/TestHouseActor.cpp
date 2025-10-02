#include "TestHouseActor.h"

TestHouseActor::TestHouseActor(ResourceType InType) : Actor(InType)
{

}

TestHouseActor::~TestHouseActor()
{
}

void TestHouseActor::OnDraw(Gdiplus::Graphics* InGraphics)
{
    Gdiplus::Pen GreenPen(Gdiplus::Color(255, 0, 255, 0), 2.0f);
    Gdiplus::PointF Positions[HouseVerticesCount];
    for (int i = 0; i < HouseVerticesCount; i++)
    {
        Positions[i] = Position + HouseVertices[i];
    }
    InGraphics->DrawPolygon(&GreenPen, Positions, HouseVerticesCount);
}