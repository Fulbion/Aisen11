#pragma once

const float pi = 3.141592653589793f;

inline float degToRad(const float degrees)
{
	return degrees * pi / 180;
}

inline float radToDeg(const float radians)
{
	return radians / pi * 180;
}