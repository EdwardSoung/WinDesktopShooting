#pragma once

class Actor;

class Component
{
public:
	Component(Actor* InOwner) : Owner(InOwner) {};
	virtual ~Component() = default;

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnTick(double InDeltaTime) {}

	inline  Actor* GetOwner() const { return Owner; }
protected:
	Actor* Owner = nullptr;
};

