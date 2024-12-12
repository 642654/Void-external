#pragma once
#include <windows.h>
#include "../memory.hpp"
#include "../reader/reader.hpp"

namespace g //globals I ain't typing allat
{
	inline bool running = true;
	inline auto mem = Memory{ L"cs2.exe" };
	inline const auto client = mem.GetModuleAddress(L"client.dll");
	inline const auto server = mem.GetModuleAddress(L"server.dll");
	inline const auto engine = mem.GetModuleAddress(L"engine.dll");
}

namespace togg //toggles
{
	inline bool thirdperson = true;
}




