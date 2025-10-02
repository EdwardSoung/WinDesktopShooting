#pragma once
#include <type_traits>
#include "Actor.h"
#include "Singleton.h"
#include "Enums.h"
#include "GameManager.h"

//Actor 생성 클래스
class Factory : public Singleton<Factory>
{
	friend class Singleton<Factory>;
public:
	template <typename T>
	typename std::enable_if < std::is_base_of<Actor, T>::value, T*>::type
	SpawnActor(ResourceType InType, RenderLayer InLayer = RenderLayer::Misc)
	{
		T* NewActor = new T(InType);
		NewActor->SetRenderLayer(InLayer);
		NewActor->OnInitialize();
		GameManager::Instance().RegistActor(InLayer, NewActor);

		return NewActor;
	}

	virtual void Initialize() override {}
	virtual void OnDestroy() override {}

private:
	Factory() = default;
	virtual ~Factory() = default;
};