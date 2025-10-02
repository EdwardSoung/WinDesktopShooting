#include "UserInterface.h"
#include "GameManager.h"
void UserInterface::UpdatePosition()
{
	// ��Ŀ�� �Ǻ��� ���	�� ��ġ�� ������Ʈ
	GameManager& gameManager = GameManager::Instance();
	Position.X = anchoredPosition.x + (anchor.X * gameManager.ScreenWidth) - (Pivot.X * width);
	Position.Y = anchoredPosition.y + (anchor.Y * gameManager.ScreenHeight) - (Pivot.Y * height);
}