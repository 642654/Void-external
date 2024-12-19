#pragma once
#include <cstddef>

namespace offs //again I ain't writing allat
{
	//client.dll
	constexpr std::ptrdiff_t localPlayer = 0x1862FB0	;
	constexpr std::ptrdiff_t entList = 0x1862FB0;
	constexpr std::ptrdiff_t thirdperson = 0x1A5E4D0; //set to 256 for thirdperson and 0 for normal
	constexpr std::ptrdiff_t viewMatrix = 0x1A54550;
	constexpr std::ptrdiff_t forceJump = 0x184E9E0;
	constexpr std::ptrdiff_t thirdPersonNop = 0x780E9D;
	constexpr std::ptrdiff_t thirdPersonCamNop = 0x782279;
	constexpr std::ptrdiff_t distFromCam = 0x1A5E4E0;
	constexpr std::ptrdiff_t viewAngles = 0x1A5E650;


	//server.dll
	constexpr std::ptrdiff_t numOfPlayers = 0x13E5CF4;


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

