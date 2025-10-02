#include "Actor.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include <algorithm>

Actor::Actor(ResourceType InType)
{
    ImageType = InType;

    Image = ResourceManager::Instance().GetResource(ImageType);
}

void Actor::OnDraw(Gdiplus::Graphics* InGraphics)
{
    if (!InGraphics) return;
    if (!Image) return;

    // ���� ��ȯ ���� ����
    //Gdiplus::Matrix oldTransform;
    //InGraphics->GetTransform(&oldTransform);

    //// ȸ�� �߽����� ��ü�� �߽����� ����
    //InGraphics->TranslateTransform(Position.X, Position.Y);

    //// ������ ������ŭ ȸ��
    //InGraphics->RotateTransform(Angle);

    // Image�� �ε��Ǿ� �ִ�.
    InGraphics->DrawImage(
        Image,          // �׷��� �̹���
        static_cast<int>(Position.X - Size * Pivot.X),    // �׷��� ��ġ
        static_cast<int>(Position.Y - Size * Pivot.Y),
        Size, Size);  // �׷��� ������

    // ���� ��ȯ ���·� ����
    //InGraphics->SetTransform(&oldTransform);
}

void Actor::AddComponent(Component* InComponent)
{
    if (InComponent)
    {
        Components.push_back(InComponent);
        InComponent->OnInitialize();
    }
}

void Actor::RemoveComponent(Component* InComponent)
{
    if (InComponent)
    {
        auto it = std::find(Components.begin(), Components.end(), InComponent);
        if (it != Components.end())
        {
            (*it)->OnDestroy(); // ������Ʈ �ı� ȣ��

            std::swap(*it, Components.back());
            Components.pop_back();   // ���� �� �� ������� ������Ʈ ����
            delete InComponent;
            InComponent = nullptr;
        }
    }
}

void Actor::DestroyActor()
{
    if (!IsPendingDestroy)
    {
        IsPendingDestroy = true;
        GameManager::Instance().RequestDestroy(this);    // �ڽ��� ���� ��û�ϱ�
    }
}
