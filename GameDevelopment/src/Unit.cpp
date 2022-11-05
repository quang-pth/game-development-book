#include "include/Unit.h"

const float PIXEL_TO_METER = 0.03125;
const float METER_TO_PIXEL = 32.0f;


b2Vec2 Unit::PixelsToMeters(const Vector2& pixels)
{
	return b2Vec2(pixels.x * PIXEL_TO_METER, pixels.y * PIXEL_TO_METER);
}

Vector2 Unit::MetersToPixels(const b2Vec2& meters)
{
	return Vector2(meters.x * METER_TO_PIXEL, meters.y * METER_TO_PIXEL);
}
