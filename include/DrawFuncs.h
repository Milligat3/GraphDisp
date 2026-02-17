// DrawFuncs.h
#pragma once
#include <raylib.h>
#include "Graph.h"

Vector2 MyVec2RayVec2(Vec2 v);

void DrawGraph(Graph graph);

void DrawMenu(int is_displayed, Graph *graph);