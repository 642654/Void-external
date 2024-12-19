#include "misc.hpp"



void Bhop()
{
	while (g::running)
	{
		
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!reader.localPlayer)
				continue;

			if (reader.entities[LOCAL_PLAYER].health <= 0 || reader.entities[LOCAL_PLAYER].health > 100)
				continue;
			
			if (reader.entities[LOCAL_PLAYER].flags == 65665)
			{
				g::mem.Write<int>(g::client + offs::forceJump, 65537);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				g::mem.Write<int>(g::client + offs::forceJump, 16777472);
				continue;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}