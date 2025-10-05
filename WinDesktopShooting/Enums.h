#pragma once
#include <cstdint>
#include <Windows.h>

enum class InputDirection : uint8_t
{
	None = 0,
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT
};

enum class RenderLayer : uint8_t
{
	Background = 0,
	Player,
	Meteor,
	UI,
	Test,
	Misc
};

enum class ResourceType : uint8_t
{
	None,
	Player,
	Meteor1,	
	Meteor2,	
	Meteor3,	
	Meteor4,	
	Meteor5,	
	Background,
	Number0,
	Number1,
	Number2,
	Number3,
	Number4,
	Number5,
	Number6,
	Number7,
	Number8,
	Number9,
	Dot,
	Test,
	Shield3,
	Shield2,
	Shield1,
};

enum class CollisionType
{
	Circle,
	Rectangle,
};

enum class PhysicsLayer
{
	None = 0,
	Player,
	Bomb
};

enum class GameState
{
	Lobby,
	Playing,
	GameOver,
};