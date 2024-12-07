#include <iostream>
#include <thread>
#include "memory.hpp"
#include "globals/globals.hpp"
#include "offsets.hpp"
#include "misc/misc.hpp"



int main()
{
	if (g::client)
		std::cout << "[+] Client.dll base address: 0x" << std::hex << g::client << '\n';
	else
		std::cout << "[-] Game not found\n";

	//start the threads
	std::thread miscThr(Misc);

	while (g::running)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			g::running = false;
		if (GetAsyncKeyState(VK_INSERT) & 1)
			togg::thirdperson = !togg::thirdperson;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	miscThr.join();

	return 0;
}