#pragma once
#include "../../extern/imgui/imgui.h"
#include "../globals/globals.hpp"
#include "../reader/reader.hpp"
#include "../structs.hpp"

void ESP();

void BoxESP();

void SkeletonESP();

bool World2Screen(Vec3 Pos, ImVec2& pixelPos);

