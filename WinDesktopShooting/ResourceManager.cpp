#include "ResourceManager.h"

void ResourceManager::Initialize()
{

}
void ResourceManager::GenerateResources()
{
    AddResource(ResourceType::Player, L"./Images/Airplane01.png");
    AddResource(ResourceType::Background, L"./Images/BG.png");
    AddResource(ResourceType::Meteor1, L"./Images/Meteor1.png");
    AddResource(ResourceType::Meteor2, L"./Images/Meteor2.png");
    AddResource(ResourceType::Meteor3, L"./Images/Meteor3.png");
    AddResource(ResourceType::Meteor4, L"./Images/Meteor4.png");
    AddResource(ResourceType::Meteor5, L"./Images/Meteor5.png");
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
    AddResource(ResourceType::Shield3, L"./Images/Shield3.png");
    AddResource(ResourceType::Shield2, L"./Images/Shield2.png");
    AddResource(ResourceType::Shield1, L"./Images/Shield1.png");
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
        //경고
    }
    return TargetResource;
}

void ResourceManager::AddResource(ResourceType Type, const WCHAR* Path)
{
    Image = new Gdiplus::Bitmap(Path);
    if (Image == NULL || Image->GetLastStatus() != Gdiplus::Ok)
    {
        //플레이어 이미지 정상 로딩 실패
        delete Image;
        Image = nullptr;
       // MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
    else
    {
        Resources.insert({ Type, Image });
    }

}
