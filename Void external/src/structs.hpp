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
	float m[16];
};



struct Bones
{
    float bones[220];
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
    char pad36[offs::crosshairId - offs::position - sizeof(pos)];
    BYTE crosshairID = 0;
    char pad4[offs::aimPunch - offs::crosshairId - sizeof(crosshairID)];
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

struct BoneConnection
{
    int bone1;
    int bone2;

    // Constructor
    BoneConnection(int b1, int b2) : bone1(b1), bone2(b2) {}
};

inline BoneConnection boneConnections[] = {
    BoneConnection(6, 5),   // head to neck
    BoneConnection(5, 4),   // neck to spine
    BoneConnection(4, 0),   // spine to hip
    BoneConnection(4, 8),   // spine to left shoulder
    BoneConnection(8, 9),   // left shoulder to left arm
    BoneConnection(9, 11),  // arm to hand
    BoneConnection(4, 13),  // spine to right shoulder
    BoneConnection(13, 14), // right shoulder to arm
    BoneConnection(14, 16), // right arm to hand
    BoneConnection(4, 2),   // spine to spine_1
    BoneConnection(0, 22),  // hip to left_hip
    BoneConnection(0, 25),  // hip to right_hip
    BoneConnection(22, 23), // left_hip to left_knee
    BoneConnection(23, 24), // left knee to left foot
    BoneConnection(25, 26), // right_hip to right_knee
    BoneConnection(26, 27)  // right knee to right foot
};