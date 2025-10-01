#include "ResourceManager.h"

void ResourceManager::GenerateResources()
{
    AddResource(ResourceType::Player, L"./Images/Airplane01.png");
    AddResource(ResourceType::Background, L"./Images/BG.png");
}

void ResourceManager::Destroy()
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
