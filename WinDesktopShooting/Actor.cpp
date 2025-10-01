#include "Actor.h"
#include "ResourceManager.h"

Actor::Actor(RenderLayer InLayer, ResourceType InType)
{
    Layer = InLayer;
    ImageType = InType;
}

void Actor::OnDraw(Gdiplus::Graphics* InGraphics)
{
    auto Image = Singleton<ResourceManager>::Instance().GetResource(ImageType);
    if (Image)
    {
        InGraphics->DrawImage(Image,
            static_cast<int>(Position.X - PixelSize * Pivot.X),
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);
    }
}