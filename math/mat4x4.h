#ifndef MATH_MAT4X4_H_
#define MATH_MAT4X4_H_


#include "Vec3.h"
#include "Vec4.h"

#ifdef RAD_SSE2
# include <emmintrin.h>
#endif // RAD_SSE2

namespace radium::math
{

struct Mat4x4
{
	float data[16];

	Mat4x4()
		: data{ 1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1 }
	{

	}

	Mat4x4(const Vec3& m) : Mat4x4()
	{
		(*this)(0,1) = m.x;
		(*this)(0,1) = m.y;
		(*this)(0,1) = m.z;
	}

	Mat4x4(float v00, float v01, float v02, float v03,
		float v10, float v11, float v12, float v13,
		float v20, float v21, float v22, float v23,
		float v30, float v31, float v32, float v33)
		: data{ v00, v01, v02, v03,
				v10, v11, v12, v13,
				v20, v21, v22, v23,
				v30, v31, v32, v33 }
	{

	}
	inline float& operator()(int i, int j)
	{
		return data[i + 4 * j];
	};

	inline float operator()(int i, int j) const
	{
		return data[i + 4 * j];
	}


	Mat4x4& operator=(const Mat4x4& m)
	{
		memcpy(data, m.data, sizeof(data));

		return *this;
	}

	bool operator==(const Mat4x4& o)
	{
		// todo: check memory access pattern
		//		 see if long if statement would suffice
		for (int i = 0; i < 16; i++)
			if (data[i] != o.data[i])
				return false;

		return true;
	}


	bool operator!=(const Mat4x4& o)
	{
		return !(*this == o);
	}

	Vec3 operator*(const Vec3& v) const
	{
		float invW = 1.0f / (data[13] * v.x +
			data[14] * v.y +
			data[15] * v.z);

		return {
			(data[5] * v.x + data[6] * v.x + data[7] * v.x) * invW,
			(data[9] * v.x + data[10] * v.x + data[11] * v.x) * invW,
			(data[13] * v.x + data[14] * v.x + data[15] * v.x) * invW

		};

	}

	Vec4 operator*(const Vec4& v) const
	{

		return {
			(data[0] * v.x + data[1] * v.y + data[2] * v.z + data[3] * v.w) ,
			(data[4] * v.x + data[5] * v.y + data[6] * v.z + data[7] * v.w) ,
			(data[8] * v.x + data[9] * v.y + data[10] * v.z + data[11] * v.w) ,
			(data[12] * v.x + data[13] * v.y + data[14] * v.z + data[15] * v.w) ,
		};
	}

	Mat4x4 operator+(const Mat4x4& m) const
	{
		return
		{
			data[0] + m.data[0],
			data[1] + m.data[1],
			data[2] + m.data[2],
			data[3] + m.data[3],
			data[4] + m.data[4],
			data[5] + m.data[5],
			data[6] + m.data[6],
			data[7] + m.data[7],
			data[8] + m.data[8],
			data[9] + m.data[9],
			data[10] + m.data[10],
			data[11] + m.data[11],
			data[12] + m.data[12],
			data[13] + m.data[13],
			data[14] + m.data[14],
			data[15] + m.data[15]
		};
	}

	Mat4x4 operator-(const Mat4x4& m) const
	{
		return
		{
			data[0] - m.data[0],
			data[1] - m.data[1],
			data[2] - m.data[2],
			data[3] - m.data[3],
			data[4] - m.data[4],
			data[5] - m.data[5],
			data[6] - m.data[6],
			data[7] - m.data[7],
			data[8] - m.data[8],
			data[9] - m.data[9],
			data[10] - m.data[10],
			data[11] - m.data[11],
			data[12] - m.data[12],
			data[13] - m.data[13],
			data[14] - m.data[14],
			data[15] - m.data[15]
		};
	}

	Mat4x4
		operator*(const Mat4x4& other) const
	{
		Mat4x4 result;

		result.data[0] = data[0] * other.data[0] + data[4] * other.data[1] + data[8] * other.data[2]
			+ data[12] * other.data[3];
		result.data[1] = data[1] * other.data[0] + data[5] * other.data[1] + data[9] * other.data[2]
			+ data[13] * other.data[3];
		result.data[2] = data[2] * other.data[0] + data[6] * other.data[1] + data[10] * other.data[2]
			+ data[14] * other.data[3];
		result.data[3] = data[3] * other.data[0] + data[7] * other.data[1] + data[11] * other.data[2]
			+ data[15] * other.data[3];

		result.data[4] = data[0] * other.data[4] + data[4] * other.data[5] + data[8] * other.data[6]
			+ data[12] * other.data[7];
		result.data[5] = data[1] * other.data[4] + data[5] * other.data[5] + data[9] * other.data[6]
			+ data[13] * other.data[7];
		result.data[6] = data[2] * other.data[4] + data[6] * other.data[5] + data[10] * other.data[6]
			+ data[14] * other.data[7];
		result.data[7] = data[3] * other.data[4] + data[7] * other.data[5] + data[11] * other.data[6]
			+ data[15] * other.data[7];

		result.data[8] = data[0] * other.data[8] + data[4] * other.data[9] + data[8] * other.data[10]
			+ data[12] * other.data[11];
		result.data[9] = data[1] * other.data[8] + data[5] * other.data[9] + data[9] * other.data[10]
			+ data[13] * other.data[11];
		result.data[10] = data[2] * other.data[8] + data[6] * other.data[9] + data[10] * other.data[10]
			+ data[14] * other.data[11];
		result.data[11] = data[3] * other.data[8] + data[7] * other.data[9] + data[11] * other.data[10]
			+ data[15] * other.data[11];

		result.data[12] = data[0] * other.data[12] + data[4] * other.data[13] + data[8] * other.data[14]
			+ data[12] * other.data[15];
		result.data[13] = data[1] * other.data[12] + data[5] * other.data[13] + data[9] * other.data[14]
			+ data[13] * other.data[15];
		result.data[14] = data[2] * other.data[12] + data[6] * other.data[13] + data[10] * other.data[14]
			+ data[14] * other.data[15];
		result.data[15] = data[3] * other.data[12] + data[7] * other.data[13] + data[11] * other.data[14]
			+ data[15] * other.data[15];

		return result;

	}

	Mat4x4 operator*(float k) const
	{
		return
		{
			data[0] * k,
			data[1] * k,
			data[2] * k,
			data[3] * k,
			data[4] * k,
			data[5] * k,
			data[6] * k,
			data[7] * k,
			data[8] * k,
			data[9] * k,
			data[10] * k,
			data[11] * k,
			data[12] * k,
			data[13] * k,
			data[14] * k,
			data[15] * k
		};
	}

	Mat4x4 transpose() const
	{
		return
		{
			data[0], data[4], data[8],  data[12],
			data[1], data[5], data[9],  data[13],
			data[2], data[6], data[10], data[14],
			data[3], data[7], data[11], data[15]
		};
	}

	void scale(float k)
	{
		data[0] = k;
		data[1] = k;
		data[2] = k;
	}

	void scale(const Vec3& v)
	{
		data[0] = v.x;
		data[1] = v.y;
		data[2] = v.z;
	}

	static const Mat4x4 ZERO;
	static const Mat4x4 IDENTITY;
};

} // radium::math


#endif // MATH_MAT4X4_H_