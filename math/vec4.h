#ifndef MATH_VEC4_H_
#define MATH_VEC4_H_

#include <cmath>
#include "vec3.h"

namespace radium::math
{

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4() : x(0), y(0), z(0), w(0) {}

	Vec4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{}


	bool operator==(const Vec4& o) const { return x == o.x && y == o.y && z == o.z && w == o.w; }
	bool operator!=(const Vec4& o) const { return x != o.x || y != o.y || z != o.z || w != o.w; }

	Vec4 operator+(const Vec4& o) const { return { x + o.x, y + o.y, z + o.z, w + o.w }; }
	Vec4 operator-(const Vec4& o) const { return { x - o.x, y - o.y, z - o.z, w - o.w }; }
	Vec4 operator*(const Vec4& o) const { return { x * o.x, y * o.y, z * o.z, w * o.w }; }
	Vec4 operator/(const Vec4& o) const { return { x / o.x, y / o.y, z / o.z, w / o.w }; }

	Vec4 operator-() const { return{ -x, -y,-z ,-w }; }

	Vec4 operator+(int k) const { return { x + k, y + k, z + k, w + k}; }
	Vec4 operator-(int k) const { return { x - k, y - k, z - k, w - k}; }
	Vec4 operator*(int k) const { return { x * k, y * k, z * k, w * k}; }
	Vec4 operator/(int k) const { return { x / k, y / k, z / k, w / k}; }


	Vec4& operator+=(const Vec4& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;

		return *this;
	}

	Vec4& operator-=(const Vec4& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;

		return *this;
	}

	Vec4& operator*=(const Vec4& o)
	{
		x *= o.x;
		y *= o.y;
		z *= o.z;

		return *this;
	}

	Vec4& operator/=(const Vec4& o)
	{
		x /= o.x;
		y /= o.y;
		z /= o.z;

		return *this;
	}

	Vec4& operator*=(int k)
	{
		x *= k;
		y *= k;
		z *= k;

		return *this;
	}

	Vec4& operator/=(int k)
	{
		float i = 1.0f / k;
		x *= i;
		y *= i;
		z *= i;

		return *this;
	}

	float length() const { return (float)sqrt(x * x + y * y + z * z + w * w); }
	float lengthSquared() const { return x * x + y * y + z * z + w * w; }

	void normalize()
	{
		float lens = lengthSquared();
		if (lens == 1.0f && lens > 0.0f)
		{
			float invlen = 1.0f / sqrtf(lens);
			x *= invlen;
			y *= invlen;
			z *= invlen;
			w *= invlen;
		}
	}

	float dot(const Vec4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }

	// Doesn't exist for R4
	// Vec4  cross(const Vec4& v) const;

	Vec3 operator()(){ return { x,y,z }; }
	
	static const Vec4 ZERO;
	static const Vec4 ONE;

};




}


#endif // MATH_VEC4_H_