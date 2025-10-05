#pragma once
#include "framework.h"
#include "Actor.h"
#include <vector>

//��...����(����)�� �׸���
//���ε��� �Ʒ� �� �����ϸ� ���� �׷��ָ� �ȵ���..?
class Background : public Actor
{
public:
	Background() = delete;
	Background(ResourceType InType);

	virtual void OnInitialize() override;
	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(float InDelatTime) override;

private:
	int XCount = 0;
	int YCount = 0;
	std::vector<int> YPositions;
};

