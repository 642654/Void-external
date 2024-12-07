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
		g::mem.Write<int>(g::client + offs::thirdperson, 256);
	else 
		g::mem.Write<int>(g::client + offs::thirdperson, 0);
}
/*
void Bhop()
{
	while (g::running)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
		{
			if (!read::localPlayer)
				continue;
			if (read::iPlayer.health <= 0 || read::iPlayer.health >= 100)
				continue;

			

			(read::iPlayer.flags == 65665) ?
			g::mem.Write<int>(g::client + offs::forceJump, 65537) :
			g::mem.Write<int>(g::client + offs::forceJump, 16777472);

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}*/