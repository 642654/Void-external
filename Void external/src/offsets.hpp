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


	//server.dll
	constexpr std::ptrdiff_t numOfPlayers = 0x13E5CF4;


	//local player
	
	constexpr std::ptrdiff_t health = 0x344;
	constexpr std::ptrdiff_t teamId = 0x3E3;
	constexpr std::ptrdiff_t flags = 0x3EC;
}

