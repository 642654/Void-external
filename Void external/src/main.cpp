#include <iostream>
#include "memory.hpp"
#include "globals/globals.hpp"
#include "offsets.hpp"
#include "misc/misc.hpp"
#include "reader/reader.hpp"
#include "legitbot/aimbot.h"


int main()
{
	if (g::client)
		std::cout << "[+] Client.dll base address: 0x" << std::hex << g::client << '\n' << std::dec;
	else
		std::cout << "[-] Game not found\n";

	//start the threads
	std::thread readerThr(&Reader::ThreadLoop, &reader);
	readerThr.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(50)); 

	std::thread miscThr(Misc);
	miscThr.detach();

	std::thread bhopThr(Bhop);
	bhopThr.detach();

	std::thread legitbotThr(Aimbot);
	legitbotThr.detach();
	

	while (g::running)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			g::running = false;
		if (GetAsyncKeyState(VK_INSERT) & 1)
			togg::thirdperson = !togg::thirdperson;


		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	readerThr.join();
	miscThr.join();
	bhopThr.join();
	legitbotThr.join();


	return 0;
}