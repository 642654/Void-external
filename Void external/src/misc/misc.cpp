#include "misc.hpp"

void Misc()
{
	while (g::running)
	{
		ThirdPerson();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}


void ThirdPerson()
{
	if (togg::thirdperson)
	{
		g::mem.PatchEx((BYTE*)(g::client + offs::thirdPersonNop), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90", 8);
		g::mem.Write<int>(g::client + offs::thirdperson, 256);
		g::mem.PatchEx((BYTE*)(g::client + offs::thirdPersonCamNop), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90", 9);
		g::mem.Write<float>(g::client + offs::distFromCam, 150);
	}
	else
	{
		g::mem.PatchEx((BYTE*)(g::client + offs::thirdPersonNop), (BYTE*)"\x44\x88\xBC\x3E\x51\x02\x00\x00", 8);
		g::mem.Write<int>(g::client + offs::thirdperson, 0);
		g::mem.PatchEx((BYTE*)(g::client + offs::thirdPersonCamNop), (BYTE*)"\xF3\x0F\x11\xBC\x3E\x60\x02\x00\x00", 9);
	}
		
}

void Bhop()
{
	while (g::running)
	{
		
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
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