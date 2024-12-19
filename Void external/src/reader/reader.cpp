#include "reader.hpp"


void Reader::GetEntities()
{
	int loop = 0;
	entities.resize(20);
	entAddr.resize(20);
	entBones.resize(20);
	while (g::running)
	{
		loop++;
		if (loop == 10)
		{
			Reader::entList = g::client + offs::entList;
			for (int i = 0; i < 20; i++)
			{
				uintptr_t address = g::mem.Read<uintptr_t>( Reader::entList + (i * 0x8));
				std::lock_guard<std::mutex> lock(entitiesMutex);
				entAddr[i] = address;
				if (i == 0)
					localPlayer = address;
			}
			loop = 0;
		}
		
		
		for (int i = 0; i < 20; i++)
		{
			entity = g::mem.Read<Entity>(entAddr[i]);
			uintptr_t boneMatrix = g::mem.Read<uintptr_t>(entity.gamescene + offs::modelState + 0x80);
			Bones bones = g::mem.Read<Bones>(boneMatrix);

			std::lock_guard<std::mutex> lock(entitiesMutex);
			matrix = g::mem.Read<Mat4x4>(g::client + offs::viewMatrix);
			entities[i] = entity;
			entBones[i] = bones;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

