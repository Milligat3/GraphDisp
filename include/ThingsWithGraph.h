// ThingsWithGraph.h
#pragma once
#include "Graph.h"


int CheckIfMouseOnSidesOfVec(Graph graph, Vec2 MousePos);
int CheckWhichToDrag(Graph graph, Vec2 MousePos);
void DragNode(Graph *graph, Vec2 MousePos);
void AddNode(Graph *graph, Vec2 MousePos, int menu_is_up);
void DeleteNode(Graph *graph, int menu_is_up);
void Init_Graph(Graph *graph);
void Check_Vert_Pos(Graph *graph);

Edge Check_If_Mouse_On_Matrix(Graph graph, Vec2 MousePos);

void Check_Vert_Pos(Graph *graph);