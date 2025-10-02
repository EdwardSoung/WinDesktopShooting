#include "ResourceManager.h"

void ResourceManager::Initialize()
{

}
void ResourceManager::GenerateResources()
{
    AddResource(ResourceType::Player, L"./Images/Airplane01.png");
    AddResource(ResourceType::Background, L"./Images/BG.png");
    AddResource(ResourceType::Bomb, L"./Images/Bomb.png");
    AddResource(ResourceType::Dot, L"./Images/Dot.png");
    AddResource(ResourceType::Number0, L"./Images/Number0.png");
    AddResource(ResourceType::Number1, L"./Images/Number1.png");
    AddResource(ResourceType::Number2, L"./Images/Number2.png");
    AddResource(ResourceType::Number3, L"./Images/Number3.png");
    AddResource(ResourceType::Number4, L"./Images/Number4.png");
    AddResource(ResourceType::Number5, L"./Images/Number5.png");
    AddResource(ResourceType::Number6, L"./Images/Number6.png");
    AddResource(ResourceType::Number7, L"./Images/Number7.png");
    AddResource(ResourceType::Number8, L"./Images/Number8.png");
    AddResource(ResourceType::Number9, L"./Images/Number9.png");
    AddResource(ResourceType::Test, L"./Images/Test.png");
}

void ResourceManager::OnDestroy()
{
    for(auto Resource : Resources)
    {
        delete Resource.second;
        Resource.second = nullptr;
    }
}

Gdiplus::Bitmap* ResourceManager::GetResource(ResourceType InType)
{
    if (InType == ResourceType::None)
        return nullptr;

    auto TargetResource = Resources[InType];
    if (TargetResource == nullptr)
    {
        //���
    }
    return TargetResource;
}

void ResourceManager::AddResource(ResourceType Type, const WCHAR* Path)
{
    Image = new Gdiplus::Bitmap(Path);
    if (Image == NULL || Image->GetLastStatus() != Gdiplus::Ok)
    {
        //�÷��̾� �̹��� ���� �ε� ����
        delete Image;
        Image = nullptr;
       // MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
    }
    else
    {
        Resources.insert({ Type, Image });
    }

}
