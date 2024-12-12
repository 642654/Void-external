#include <iostream>
#include "memory.hpp"
#include "globals/globals.hpp"
#include "offsets.hpp"
#include "misc/misc.hpp"
#include "reader/reader.hpp"



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

	

	while (g::running)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			g::running = false;
		if (GetAsyncKeyState(VK_INSERT) & 1)
			togg::thirdperson = !togg::thirdperson;


		for (int i = 0; i < reader.numOfEnts; i++)
		{
			std::cout << "This nigga has " << reader.entities[i].health << "hp \n";
			std::cout << reader.entities[0].health << '\n';
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	readerThr.join();
	miscThr.join();
	bhopThr.join();
	


	return 0;
}