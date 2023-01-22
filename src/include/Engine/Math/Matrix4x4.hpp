#pragma once

#include <memory>
#include <cmath>

#include "Engine/Math/Vector2D.hpp"
#include "Engine/Math/Vector3D.hpp"
#include "Engine/Math/Vector4D.hpp"

template<typename T>
class Matrix4x4
{
public:
	Matrix4x4()
	{
	}

	void setIdentity()
	{
		memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void scale(const Vector3D<T>& size)
	{
		mat[0][0] = size.x;
		mat[1][1] = size.y;
		mat[2][2] = size.z;
	}

	void translate(const Vector3D<T>& translation)
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

	void rotateX(float x)
	{
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void rotateY(float y)
	{
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void rotateZ(float z)
	{
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	float getDeterminant()
	{
		Vector4f minor, v1, v2, v3;
		float det;

		v1 = Vector4f(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
		v2 = Vector4f(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
		v3 = Vector4f(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z + this->mat[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4f v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->mat[j][0]);
					vec[a].y = (this->mat[j][1]);
					vec[a].z = (this->mat[j][2]);
					vec[a].w = (this->mat[j][3]);
				}
			}

			v.cross(vec[0], vec[1], vec[2]);

			out.mat[0][i] = pow(-1.0f, i) * v.x / det;
			out.mat[1][i] = pow(-1.0f, i) * v.y / det;
			out.mat[2][i] = pow(-1.0f, i) * v.z / det;
			out.mat[3][i] = pow(-1.0f, i) * v.w / det;
		}

		this->setMatrix(out);
	}

	void operator *=(const Matrix4x4<T>& matrix)
	{
		Matrix4x4<T> out;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
			}
		}

		setMatrix(out);
	}

	void setMatrix(const Matrix4x4<T>& matrix)
	{
		memcpy(mat, matrix.mat, sizeof(float) * 16);
	}

	Vector3f getXDirection()
	{
		return Vector3f(mat[0][0], mat[0][1], mat[0][2]);
	}

	Vector3f getZDirection()
	{
		return Vector3f(mat[2][0], mat[2][1], mat[2][2]);
	}

	Vector3f getTranslation()
	{
		return Vector3f(mat[3][0], mat[3][1], mat[3][2]);
	}

	void setPrespectiveFovLH(T fov, T aspect, T zNear, T zFar)
	{
		float yScale = 1.0f / tan(fov / 2.0);
		float xScale = yScale / aspect;
		mat[0][0] = xScale;
		mat[1][1] = yScale;
		mat[2][2] = zFar / (zFar - zNear);
		mat[2][3] = 1.0f;
		mat[3][2] = (-zNear * zFar) / (zFar - zNear);
	}

	void setOrthoLH(T width, T height, T nearPlane, float farPlane)
	{
		setIdentity();
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	T mat[4][4] = {};
};

typedef Matrix4x4<int> int4x4;
typedef Matrix4x4<float> float4x4;
typedef Matrix4x4<UINT> uint4x4;