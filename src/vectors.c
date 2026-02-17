#include "vectors.h"
#include <math.h>

Vec2 make_vector(float x, float y){
	return (Vec2) {x, y};
}

Vec2 vec_sub(Vec2 v1, Vec2 v2){
	return make_vector(v1.x - v2.x, v1.y - v2.y);
}
float vec_length(Vec2 vec){
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

