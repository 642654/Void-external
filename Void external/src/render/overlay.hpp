#pragma once
#include <windows.h>
#include <dwmapi.h>
#include <iostream>
#include <d3d11.h>
#include "../../extern/imgui/imgui.h"
#include "../../extern/imgui/imgui_impl_dx11.h"
#include "../../extern/imgui/imgui_impl_win32.h"
#include "../globals/globals.hpp"
#include "ESP.hpp"


void InitOverlay();
void BeginRender();
void Render();
void EndRender();
void UninitOverlay();
