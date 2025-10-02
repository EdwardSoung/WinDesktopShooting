#pragma once
#include "framework.h"
#include "Enums.h"
#include "Singleton.h"
#include <unordered_map>

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	virtual void Initialize() override;
	virtual void OnDestroy() override;
	void GenerateResources();

	Gdiplus::Bitmap* GetResource(ResourceType InResource);
	
	Gdiplus::Bitmap* Image = nullptr;

private:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	std::unordered_map<ResourceType, Gdiplus::Bitmap*> Resources;

	void AddResource(ResourceType Type, const WCHAR* Path);
};

