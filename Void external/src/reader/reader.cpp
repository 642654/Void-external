#include "reader.hpp"


void Reader::GetEntities()
{
	Reader::entList = g::client + offs::entList;
	Reader::numOfEnts = g::mem.Read<int>(g::server + offs::numOfPlayers);
	entities.resize(numOfEnts); //resize the vector so i can access it without the retarded asserts


	for (int i = 0; i < Reader::numOfEnts; i++)
	{
		uintptr_t playerAddr = g::mem.Read<uintptr_t>(Reader::entList + (i * 0x10));
		entity = g::mem.Read<Entity>(playerAddr);

		std::lock_guard<std::mutex> lock(entitiesMutex);
		if (i == 0)
		{
			localPlayer = g::mem.Read<uintptr_t>(Reader::entList);
		}
		entities[i] = entity;
	}
}

void Reader::ThreadLoop()
{
	while (g::running)
	{
		GetEntities();
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}
