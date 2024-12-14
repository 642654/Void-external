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

struct Bones
{
    float bones[180];
};




struct Entity
{
	char pad239[offs::gamescene];
	uintptr_t gamescene = 0;
	char pad0[offs::health - offs::gamescene - sizeof(gamescene)];
	int health = 0;
	char pad1[offs::teamId - offs::health - sizeof(health)];
	int8_t teamId = 0;
	char pad2[offs::flags - offs::teamId - sizeof(teamId)];
	int flags = 0;
	char pad3[offs::position - offs::flags - sizeof(flags)];
	Vec3 pos{ 0,0,0 };
    char pad4[offs::aimPunch - offs::position - sizeof(pos)];
    Vec2 aimPunch{ 0,0 };
    char pad5[offs::shotsFired - offs::aimPunch - sizeof(aimPunch)];
    int shotsFired = 0;
};

enum bones : int
{
    head = 6,
    neck = 5,
    spine = 4,
    spine_1 = 2,
    hip = 0,
    left_shoulder = 8,
    left_arm = 9,
    left_hand = 10,
    pelvis = 0,
    right_shoulder = 13,
    right_arm = 14,
    right_hand = 15,
    left_hip = 22,
    left_knee = 23,
    left_feet = 24,
    right_hip = 25,
    right_knee = 26,
    right_feet = 27
};