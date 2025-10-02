#pragma once
#include "framework.h"
#include "Actor.h"

//��...����(����)�� �׸���
//���ε��� �Ʒ� �� �����ϸ� ���� �׷��ָ� �ȵ���..?
class Background : public Actor
{
public:
	Background() = delete;
	Background(ResourceType InType);

	virtual void OnDraw(Gdiplus::Graphics* InGraphics) override;
	virtual void OnTick(double InDelatTime) override;

private:
	bool IsDraw = false;
	double ScrollSpeed = 50.0;
	float Offset = 0.0f;
};

