#include <iostream>
#include "memory.hpp"
#include "globals/globals.hpp"
#include "offsets.hpp"
#include "misc/misc.hpp"
#include "reader/reader.hpp"


Reader reader;
int main()
{
	if (g::client)
		std::cout << "[+] Client.dll base address: 0x" << std::hex << g::client << '\n' << std::dec;
	else
		std::cout << "[-] Game not found\n";

	//start the threads
	std::thread miscThr(Misc);
	miscThr.detach();

	std::thread readerThr(&Reader::ThreadLoop, &reader);
	readerThr.detach();

	while (g::running)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			g::running = false;
		if (GetAsyncKeyState(VK_INSERT) & 1)
			togg::thirdperson = !togg::thirdperson;


		for (const auto& entities : reader.entities)
		{
			std::cout << "This nigga has " << entities.health << "hp \n";
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	miscThr.join();
	readerThr.join();


	return 0;
}