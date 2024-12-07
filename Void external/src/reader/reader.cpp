#include "reader.hpp"


void Reader::GetEntities()
{
	Reader::entities.clear();

	Reader::entList = g::client + offs::entList;
	Reader::numOfEnts = g::mem.Read<int>(g::server + offs::numOfPlayers);

	for (int i = 0; i < Reader::numOfEnts; i++)
	{
		uintptr_t playerAddr = g::mem.Read<uintptr_t>(Reader::entList + (i * 0x10));
		entity = g::mem.Read<Entity>(playerAddr);
		std::lock_guard<std::mutex> lock(entitiesMutex);
		entities.push_back(entity);
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
