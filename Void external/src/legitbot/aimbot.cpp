#include "aimbot.h"

void Aimbot()
{
	while (g::running)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (!reader.localPlayer)
			continue;

		Vec2 RCSangles = RCS();
		

		Vec3 deltaVec;
		float bestDistance = FLT_MAX;
		for (int i = 1; i < reader.numOfEnts; i++) //exclude myself from the loop
		{
			if (reader.entities[i].health <= 0 || reader.entities[i].health > 100)
				continue;
			if (reader.entities[i].teamId == reader.entities[LOCAL_PLAYER].teamId)
				continue;

			Vec3 deltaVecTemp = { 
			reader.entBones[i].bones[8 * head] - reader.entBones[LOCAL_PLAYER].bones[8 * head], //ahh yes i love my weird ass logic
			reader.entBones[i].bones[8 * head + 1] - reader.entBones[LOCAL_PLAYER].bones[8 * head + 1], //so the 8 is the number of floats between the bone positions
			reader.entBones[i].bones[8 * head + 2] - reader.entBones[LOCAL_PLAYER].bones[8 * head + 2] }; 

			float distance = sqrtf(pow(deltaVecTemp.x, 2) + pow(deltaVecTemp.y, 2) + pow(deltaVecTemp.z, 2));

			if (distance < bestDistance)
			{
				bestDistance = distance;
				deltaVec = deltaVecTemp;
			}
			
		}
		if (bestDistance == FLT_MAX)
			continue;

		Vec2 angles;
		angles.x = -asinf(deltaVec.z / bestDistance) * (180 / PI);
		angles.y = atan2f(deltaVec.y, deltaVec.x) * (180 / PI);

		angles.x += RCSangles.x;
		angles.y += RCSangles.y;

		if (angles.x > 89.f)
			angles.x = 89.f;
		if (angles.x < -89.f)
			angles.x = -89.f;

		while (angles.y > 180.f)
			angles.y -= 360.f;
		while (angles.y < -180.f)
			angles.y += 360.f;
		

		g::mem.Write(g::client + offs::viewAngles, angles.x);
		g::mem.Write(g::client + offs::viewAngles + 4, angles.y);
	}
}