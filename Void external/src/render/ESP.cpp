#include "ESP.hpp"

void ESP()
{
	SkeletonESP();
}

void SkeletonESP()
{
	ImVec2 pixelPos;
	for (int i = 1; i < 20; i++)
	{
		if (reader.entities[i].health <= 0)
			continue;


		if (!World2Screen(reader.entities[i].pos, pixelPos))
			continue;


		for (int i2 = 0; i2 < sizeof(boneConnections) / sizeof(BoneConnection); i2++)
		{
			int bone1 = boneConnections[i2].bone1;
			int bone2 = boneConnections[i2].bone2;

			ImVec2 pixelPos1;
			ImVec2 pixelPos2;

			Vec3 bonePos1{ reader.entBones[i].bones[8 * bone1], reader.entBones[i].bones[8 * bone1 + 1], reader.entBones[i].bones[8 * bone1 + 2] };
			Vec3 bonePos2{ reader.entBones[i].bones[8 * bone2], reader.entBones[i].bones[8 * bone2 + 1], reader.entBones[i].bones[8 * bone2 + 2] };
			if (!World2Screen(bonePos1, pixelPos1))
				continue;
			if (!World2Screen(bonePos2, pixelPos2))
				continue;
			ImGui::GetBackgroundDrawList()->AddLine(pixelPos1, pixelPos2, IM_COL32(255, 255, 255, 255), 2);
		}

	}
}


void BoxESP()
{
	ImVec2 pixelPos;
	for (int i = 1; i < reader.numOfEnts; i++)
	{
		if (reader.entities[i].health <= 0)
			continue;
		
		if (!World2Screen(reader.entities[i].pos, pixelPos))
			continue;

		Vec3 deltaVecTemp = {
			reader.entities[i].pos.x - reader.entities[LOCAL_PLAYER].pos.x,
			reader.entities[i].pos.y - reader.entities[LOCAL_PLAYER].pos.x,
			reader.entities[i].pos.z - reader.entities[LOCAL_PLAYER].pos.x};

		float distance = sqrtf(pow(deltaVecTemp.x, 2) + pow(deltaVecTemp.y, 2) + pow(deltaVecTemp.z, 2));

		float distAdj = 850.f / distance;

		ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2(pixelPos.x - 50.f * distAdj, pixelPos.y - 200.f * distAdj),
		ImVec2(pixelPos.x + 50.f * distAdj, pixelPos.y + 10.f * distAdj),
		IM_COL32(255, 255, 255, 255), 0, 0, 2.f);

	}
}

bool World2Screen(Vec3 Pos, ImVec2& pixelPos)
{
	float wComp = reader.matrix.m[12] * Pos.x + reader.matrix.m[13] * Pos.y + reader.matrix.m[14] * Pos.z + reader.matrix.m[15];

	if (wComp < 0.01f)
		return false;

	float scrCenterX = g::screenWidth * .5f;
	float scrCenterY = g::screenHeight * .5f;

	float invWComp = 1.0f / wComp;
	pixelPos.x = scrCenterX + (reader.matrix.m[0] * Pos.x + reader.matrix.m[1] * Pos.y + reader.matrix.m[2] * Pos.z + reader.matrix.m[3]) * invWComp * scrCenterX;
	pixelPos.y = scrCenterY - (reader.matrix.m[4] * Pos.x + reader.matrix.m[5] * Pos.y + reader.matrix.m[6] * Pos.z + reader.matrix.m[7]) * invWComp * scrCenterY;

	return true;
}

