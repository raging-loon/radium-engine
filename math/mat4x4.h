#ifndef MATH_MAT4X4_H_
#define MATH_MAT4X4_H_

#include "vec3.h"
#include "vec4.h"
#ifdef TE_US_SSE2
# include <emmintrin.h>
#endif // TE_US_SSE2

namespace radium::math
{

struct Mat4x4
{
	
	Mat4x4()
		: m00(1), m01(0), m02(0), m03(0),
		  m10(0), m11(1), m12(0), m13(0),
		  m20(0), m21(0), m22(1), m23(0),
		  m30(0), m31(0), m32(0), m33(1)
	{}
	
	Mat4x4(float v00, float v01, float v02, float v03,
		float v10, float v11, float v12, float v13,
		float v20, float v21, float v22, float v23,
		float v30, float v31, float v32, float v33 ) 
	
		: m00(v00), m01(v01), m02(v02), m03(v03),
		  m10(v10), m11(v11), m12(v12), m13(v13),
		  m20(v20), m21(v21), m22(v22), m23(v23),
		  m30(v30), m31(v31), m32(v32), m33(v33)
	{	}
	
	Mat4x4(const Vec3& m) : Mat4x4()
	{
		m03 = m.x;
		m13 = m.y;
		m23 = m.z;
	}
	Mat4x4& operator=(const Mat4x4& m)
	{

		m00 = m.m00;
		m10 = m.m10;
		m20 = m.m20;
		m30 = m.m30;
		m01 = m.m01;
		m11 = m.m11;
		m21 = m.m21;
		m31 = m.m31;
		m02 = m.m02;
		m12 = m.m12;
		m22 = m.m22;
		m32 = m.m32;
		m03 = m.m03;
		m13 = m.m13;
		m23 = m.m23;
		m33 = m.m33;

		return *this;
	}

	bool operator==(const Mat4x4& m) const
	{
		return (
			m00 == m.m00 &&
			m10 == m.m10 &&
			m20 == m.m20 &&
			m30 == m.m30 &&
			m01 == m.m01 &&
			m11 == m.m11 &&
			m21 == m.m21 &&
			m31 == m.m31 &&
			m02 == m.m02 &&
			m12 == m.m12 &&
			m22 == m.m22 &&
			m32 == m.m32 &&
			m03 == m.m03 &&
			m13 == m.m13 &&
			m23 == m.m23 &&
			m33 == m.m33
		);
	}

	bool operator!=(const Mat4x4& m) const { return !(*this == m); }
	
	Vec3 operator*(const Vec3& v) const
	{

		float invW = 1.0f / (m30 * v.x + m31 * v.y + m32 * v.z + m33);

		return {
			(m11 * v.x + m12 * v.y + m13 * v.z)* invW,
			(m21 * v.x + m22 * v.y + m23 * v.z)* invW,
			(m31 * v.x + m32 * v.y + m33 * v.z) * invW,
		};
	}

	Vec4 operator*(const Vec4& v) const
	{

		return {
			(m00 * v.x + m01 * v.y + m02 * v.z + m03 * v.w) ,
			(m10 * v.x + m11 * v.y + m12 * v.z + m13 * v.w) ,
			(m20 * v.x + m21 * v.y + m22 * v.z + m23 * v.w) ,
			(m30 * v.x + m31 * v.y + m32 * v.z + m33 * v.w) ,
		};
	}

	Mat4x4 operator+(const Mat4x4& m) const
	{
		return {
			m00 + m.m00,
			m01 + m.m01,
			m02 + m.m02,
			m03 + m.m03,
			m10 + m.m10,
			m11 + m.m11,
			m12 + m.m12,
			m13 + m.m13,
			m20 + m.m20,
			m21 + m.m21,
			m22 + m.m22,
			m23 + m.m23,
			m30 + m.m30,
			m31 + m.m31,
			m32 + m.m32,
			m33 + m.m33
		};
	}

	Mat4x4 operator-(const Mat4x4& m) const
	{
		return {
			m00 - m.m00,
			m01 - m.m01,
			m02 - m.m02,
			m03 - m.m03,
			m10 - m.m10,
			m11 - m.m11,
			m12 - m.m12,
			m13 - m.m13,
			m20 - m.m20,
			m21 - m.m21,
			m22 - m.m22,
			m23 - m.m23,
			m30 - m.m30,
			m31 - m.m31,
			m32 - m.m32,
			m33 - m.m33
		};
	}

	Mat4x4 operator*(const Mat4x4& m) const
	{
		return {
			m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30,
			m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31,
			m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32,
			m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33,
			m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30,
			m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31,
			m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32,
			m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33,
			m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30,
			m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31,
			m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32,
			m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33,
			m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30,
			m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31,
			m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32,
			m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33
		};
	}

	Mat4x4 operator*(float k) const
	{
		return {
			m00 * k,
			m01 * k,
			m02 * k,
			m03 * k,
			m10 * k,
			m11 * k,
			m12 * k,
			m13 * k,
			m20 * k,
			m21 * k,
			m22 * k,
			m23 * k,
			m30 * k,
			m31 * k,
			m32 * k,
			m33 * k
		};
	}

	Mat4x4 transpose() const
	{

		return {
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		};
	}

	void setScale(const Vec3& scale)
	{
		m00 = scale.x;
		m11 = scale.y;
		m22 = scale.z;
	}

	void setScale(float k)
	{
		m00 = k;
		m11 = k;
		m22 = k;
	}

	void setTranslation(const Vec3& translation)
	{
		m03 = translation.x;
		m13 = translation.y;
		m23 = translation.z;
	}




	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;


	static const Mat4x4 ZERO;
	static const Mat4x4 IDENTITY;
};

}

#endif // MATH_MAT4X4_H_