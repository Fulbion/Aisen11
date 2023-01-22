#pragma once

template<typename T>
class Vector2D
{
public:
	Vector2D()
	{
	}

	Vector2D(T a) :
		x(a), y(a)
	{
	}

	Vector2D(T x, T y) :
		x(x), y(y)
	{
	}

	Vector2D(const Vector2D& vector2d) :
		x(vector2d.x), y(vector2d.y)
	{
	}

	static Vector2D<T> lerp(const Vector2D<T>& start, const Vector2D<T>& end, float delta)
	{
		Vector2D<T> v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);

		return v;
	}

	Vector2D<T> operator +(Vector2D<T> vec)
	{
		return Vector2D(x + vec.x, y + vec.y);
	}

	Vector2D<T> operator *(Vector2D<T> vec)
	{
		return Vector2D(x + vec.x, y + vec.y);
	}

	Vector2D<T> operator *(T m)
	{
		return Vector2D(x * m, y * m);
	}

	~Vector2D()
	{
	}

	T x, y;
};

typedef Vector2D<int> Vector2i;
typedef Vector2D<float> Vector2f;
typedef Vector2D<UINT> Vector2u;

typedef Vector2D<int> int2;
typedef Vector2D<float> float2;
typedef Vector2D<UINT> uint2;