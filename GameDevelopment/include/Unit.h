#pragma once

#include"include/CustomMath.h"
#include<box2d/b2_math.h>

class Unit {
public:
	static b2Vec2 PixelsToMeters(const Vector2& pixels);
	static float PixelsToMeters(float pixels);
	static Vector2 MetersToPixels(const b2Vec2& meters);
	static float MetersToPixels(float meters);
};