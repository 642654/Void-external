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
	uintptr_t localPlayer;
	int numOfEnts = 0;
	void ThreadLoop();
private:

	void GetEntities();
	uintptr_t entList;
	std::mutex entitiesMutex;
};

inline Entity entity;
inline Reader reader;