// Vectors.h
#pragma once

typedef struct
{
	float x, y;
}Vec2;

Vec2 make_vector(float x, float y);
Vec2 vec_sub(Vec2 v1, Vec2 v2);
float vec_length(Vec2 vec);