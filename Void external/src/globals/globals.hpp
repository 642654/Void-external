#pragma once
#include <vector>
#include "../memory.hpp"
#include "../structs.hpp"
#include "../offsets.hpp"

namespace g //globals I ain't typing allat
{
	inline bool running = true;
	inline const auto mem = Memory{ L"cs2.exe" };
	inline const auto client = mem.GetModuleAddress(L"client.dll");
	inline const auto server = mem.GetModuleAddress(L"server.dll");
	inline const auto engine = mem.GetModuleAddress(L"engine.dll");
}

namespace togg //toggles
{
	inline bool thirdperson = false;
}


class Reader
{
public:
	uintptr_t localPlayer = 0;
	
	std::vector<Entity> entities;
	

	void ThreadLoop();
private:

	void FilterEntities();
	uintptr_t entList = g::client + offs::entList;
	int numOfEnts = 0;
};

