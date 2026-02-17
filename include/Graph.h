// Graph.h
#pragma once

#include "vectors.h"
typedef struct{
	Vec2 pos;
	Vec2 dir;
	Vec2 vel;
}Vert;

typedef struct {
	short int x;
	short int y;
}Edge;

typedef struct {
	Vert *Verts;
	int **matrix_of_contiguity;
	int size;
	// Game State
	int grab;
	int index;
	// Globals
	float stifness;
	float t_g;
	float repulsion;
}Graph;
