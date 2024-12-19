#include "reader.hpp"


void Reader::GetEntities()
{
	int loop = 0;
	entities.resize(64);
	entAddr.resize(64);
	entBones.resize(64);
	while (g::running)
	{
		loop++;
		if (loop == 10)
		{
			Reader::entList = g::client + offs::entList;
			Reader::numOfEnts = g::mem.Read<int>(g::server + offs::numOfPlayers);
			for (int i = 0; i < numOfEnts; i++)
			{
				uintptr_t address = g::mem.Read<uintptr_t>( Reader::entList + (i * 0x10));
				
				entAddr[i] = address;
				if (i == 0)
					localPlayer = address;
			}
			loop = 0;
		}
		
		
		for (int i = 0; i < Reader::numOfEnts; i++)
		{
			entity = g::mem.Read<Entity>(entAddr[i]);
			uintptr_t boneMatrix = g::mem.Read<uintptr_t>(entity.gamescene + offs::modelState + 0x80);
			Bones bones = g::mem.Read<Bones>(boneMatrix);

			std::lock_guard<std::mutex> lock(entitiesMutex);
			
			entities[i] = entity;
			entBones[i] = bones;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

