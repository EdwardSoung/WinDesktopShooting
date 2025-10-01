#pragma once
#include "framework.h"
#include "Enums.h"
#include "Singleton.h"
#include <unordered_map>

class ResourceManager
{
public:

	void Destroy();
	void GenerateResources();

	Gdiplus::Bitmap* GetResource(ResourceType InResource);
	
	Gdiplus::Bitmap* Image = nullptr;
private:
	std::unordered_map<ResourceType, Gdiplus::Bitmap*> Resources;

	void AddResource(ResourceType Type, const WCHAR* Path);
};

