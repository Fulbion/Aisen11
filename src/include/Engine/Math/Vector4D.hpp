#pragma once

template<typename T>
class Vector4D
{
public:
	Vector4D()
	{
	}

	Vector4D(T a) :
		x(a), y(a), z(a)
	{
	}

	Vector4D(T x, T y, T z, T w) :
		x(x), y(y), z(z), w(w)
	{
	}

	Vector4D(const Vector4D& vector4d) :
		x(vector4d.x), y(vector4d.y), z(vector4d.z), w(vector4d.w)
	{
	}

	static Vector4D<T> lerp(const Vector4D<T>& start, const Vector4D<T>& end, float delta)
	{
		Vector4D<T> v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		v.w = start.w * (1.0f - delta) + end.w * (delta);

		return v;
	}

	void cross(Vector4D<T>& v1, Vector4D<T>& v2, Vector4D<T>& v3)
	{
		this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
		this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
		this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
		this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

	Vector4D<T> operator +(Vector4D<T> vec)
	{
		return Vector4D(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	Vector4D<T> operator *(Vector4D<T> vec)
	{
		return Vector4D(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	Vector4D<T> operator *(T m)
	{
		return Vector4D(x * m, y * m, z * m, w * m);
	}

	~Vector4D()
	{
	}

	T x, y, z, w;
};

typedef Vector4D<int> Vector4i;
typedef Vector4D<float> Vector4f;
typedef Vector4D<UINT> Vector4u;

typedef Vector4D<int> int4;
typedef Vector4D<float> float4;
typedef Vector4D<UINT> uint4;