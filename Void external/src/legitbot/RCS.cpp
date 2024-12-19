#include "RCS.hpp"

Vec2 RCS()
{
	Vec2 oldPunch;

	Vec2 angles{ 0,0 };

	if (!reader.entities[LOCAL_PLAYER].shotsFired)
	{
		oldPunch.x = oldPunch.y = 0.f;
		return Vec2(0, 0);
	}

	angles.x = oldPunch.x - reader.entities[LOCAL_PLAYER].aimPunch.x * 2.f;
	angles.y = oldPunch.y - reader.entities[LOCAL_PLAYER].aimPunch.y * 2.f;

	oldPunch.x = reader.entities[LOCAL_PLAYER].aimPunch.x * 2.f;
	oldPunch.y = reader.entities[LOCAL_PLAYER].aimPunch.y * 2.f;

	return angles;
}