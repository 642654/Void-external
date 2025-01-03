#pragma once
#include <vector>
#include <thread>
#include <windows.h>
#include <mutex>
#include "../structs.hpp"
#include "../globals/globals.hpp"
#include "../offsets.hpp"

#define LOCAL_PLAYER 0  //for the entities vector

class Reader
{
public:
	std::vector<Entity> entities;
	std::vector<Bones> entBones;
	Mat4x4 matrix;
	uintptr_t localPlayer;
	int numOfEnts = 0;
	void GetEntities();
private:
	uintptr_t entList;
	std::vector<uintptr_t> entAddr;
	std::mutex entitiesMutex;
};

inline Entity entity;
inline Reader reader;