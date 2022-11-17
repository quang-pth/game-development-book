#pragma once

#include"include/CustomMath.h"
#include<box2d/b2_math.h>

#define TILE_SIZE 16
#define TILE_PER_ROW 94

class Unit {
public:
	static b2Vec2 PixelsToMeters(const Vector2& pixels);
	static float PixelsToMeters(float pixels);
	static Vector2 MetersToPixels(const b2Vec2& meters);
	static float MetersToPixels(float meters);
};