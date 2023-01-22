#pragma once

template<typename T>
class Vector3D
{
public:
	Vector3D()
	{
	}

	Vector3D(T x, T y, T z) :
		x(x), y(y), z(z)
	{
	}

	Vector3D(const Vector3D<T>& vector3d) :
		x(vector3d.x), y(vector3d.y), z(vector3d.z)
	{
	}

	static Vector3D<T> lerp(const Vector3D<T>& start, const Vector3D<T>& end, float delta)
	{
		Vector3D<T> v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		
		return v;
	}

	Vector3D<T> operator +(Vector3D<T> vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3D<T> operator *(Vector3D<T> vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3D<T> operator *(T m)
	{
		return Vector3D(x * m, y * m, z * m);
	}

	~Vector3D()
	{
	}

	T x, y, z;
};

typedef Vector3D<int> Vector3i;
typedef Vector3D<float> Vector3f;
typedef Vector3D<UINT> Vector3u;

typedef Vector3D<int> int3;
typedef Vector3D<float> float3;
typedef Vector3D<UINT> uint3;