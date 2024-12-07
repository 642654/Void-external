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

	void ThreadLoop();
private:

	void GetEntities();
	uintptr_t entList;
	int numOfEnts = 0;
	std::mutex entitiesMutex;
};

inline Entity entity;