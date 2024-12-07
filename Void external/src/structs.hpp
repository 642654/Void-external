#pragma once
#include "offsets.hpp"

struct Vec2
{
	float x{};
	float y{};
};

struct Vec3
{
	float x{};
	float y{};
	float z{};
};

struct Mat4x4
{
	float matrix[16];
};

struct Entity
{
	char pad0[offs::health];
	int health = 0;
	char pad1[offs::teamId - offs::health - sizeof(int)];
	int8_t teamId = 0;
	char pad2[offs::flags - offs::teamId - sizeof(int8_t)];
	int flags = 0;
};