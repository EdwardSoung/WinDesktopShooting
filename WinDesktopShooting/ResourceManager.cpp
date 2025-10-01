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
