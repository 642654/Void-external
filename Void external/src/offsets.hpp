#pragma once
#include <cstddef>

namespace offs //again I ain't writing allat
{
	//client.dll
	constexpr std::ptrdiff_t localPlayer = 0x1864CC8;
	constexpr std::ptrdiff_t entList = 0x1871FB0;
	constexpr std::ptrdiff_t viewMatrix = 0x1A63C10;
	constexpr std::ptrdiff_t forceJump = 0x185D9D0;
	constexpr std::ptrdiff_t viewAngles = 0x1A6DD10;


	//server.dll
	constexpr std::ptrdiff_t numOfPlayers = 0x13E8CF4;


	//local player
	constexpr std::ptrdiff_t gamescene = 0x328;
	constexpr std::ptrdiff_t health = 0x344;
	constexpr std::ptrdiff_t teamId = 0x3E3;
	constexpr std::ptrdiff_t flags = 0x3EC;
	constexpr std::ptrdiff_t position = 0x1324;
	constexpr std::ptrdiff_t crosshairId = 0x1458;
	constexpr std::ptrdiff_t aimPunch = 0x1584;
	constexpr std::ptrdiff_t shotsFired = 0x23FC;

	
	//gamescene
	constexpr std::ptrdiff_t modelState = 0x170; // add 0x80 for view matrix
}

