#pragma once
#include "framework.h"
#include "Enums.h"
#include "Component.h"
#include <type_traits>
#include <vector>

class Actor
{
public:
	Actor() = delete;
	Actor(ResourceType InType);
	virtual ~Actor() {}

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnDraw(Gdiplus::Graphics* InGraphics);
	virtual void OnTick(double InDeltaTime) {}

	virtual void OnOverlap(Actor* InOther) {};	//다른 액터와 겹쳤을 때 자동으로 호출되는 함수...

	void AddComponent(Component* InComponent);
	void RemoveComponent(Component* InComponent);

	template<typename T>
	T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		for (auto comp : Components)
		{
			T* castComp = dynamic_cast<T*>(comp);
			if (castComp)
			{
				return castComp;
			}
		}
		return nullptr;
	}
	template<typename T>
	bool HasComponent() const
	{
		return GetComponent<T>() != nullptr;
	}

	void DestroyActor();

	//Getter
	inline int BorderSize() { return PixelSize - BorderPixel; }
	inline RenderLayer GetLayer() { return Layer; }
	inline Gdiplus::PointF GetPosition(){return Position;}

	//Setter
	inline void UpdatePosition(Gdiplus::PointF InPosition)
	{
		Position = InPosition;
	}
	inline void UpdatePosition(float InX, float InY)
	{
		Position.X = InX;
		Position.Y = InY;
	}
	inline void UpdatePivot(float InX, float InY)
	{
		Pivot.X = InX;
		Pivot.Y = InY;
	}
	inline void SetLayer(RenderLayer InLayer)
	{
		Layer = InLayer;
	}
	inline void SetSize(int InSize) { Size = InSize; }
	inline void SetRenderLayer(RenderLayer InLayer) { Layer = InLayer; }

protected:
	const int PixelSize = 64;
	Gdiplus::PointF Pivot = { 0.5f, 0.5f };
	Gdiplus::PointF Position;
	ResourceType ImageType = ResourceType::None;
	// 각도
	float Angle = 0.0f;

	// 크기
	int Size = 64;

	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이		
	std::vector<Component*> Components;
private:
	const int BorderPixel = 3;
	RenderLayer Layer = RenderLayer::Misc;

	bool IsPendingDestroy = false;
};

