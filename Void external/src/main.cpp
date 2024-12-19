#include <iostream>
#include "memory/memory.hpp"
#include "globals/globals.hpp"
#include "offsets.hpp"
#include "misc/misc.hpp"
#include "reader/reader.hpp"
#include "legitbot/aimbot.hpp"
#include "render/overlay.hpp"


int main()
{
	if (g::client)
		std::cout << "[+] Client.dll base address: 0x" << std::hex << g::client << '\n' << std::dec;
	else
	{
		std::cout << "[-] Game not found\n";
		return -1;
	}

	//start the threads
	std::thread readerThr(&Reader::GetEntities, &reader);
	readerThr.detach();
	

	std::this_thread::sleep_for(std::chrono::milliseconds(50));  // wait for the first read

	std::thread miscThr(Misc);
	miscThr.detach();

	std::thread bhopThr(Bhop);
	bhopThr.detach();

	std::thread legitbotThr(Aimbot);
	legitbotThr.detach();

	InitOverlay();
	

	while (g::running)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			g::running = false;
		if (GetAsyncKeyState(VK_INSERT) & 1)
			togg::thirdperson = !togg::thirdperson;

		BeginRender();
		Render();
		EndRender();


		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	UninitOverlay();
	readerThr.join();
	miscThr.join();
	bhopThr.join();
	legitbotThr.join();

	

	return 0;
}