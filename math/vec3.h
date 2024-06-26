#ifndef MATH_VEC3_H_
#define MATH_VEC3_H_

#include <cmath>
namespace radium::math
{

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() : x(0), y(0), z(0) {}

	Vec3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{}


	bool operator==(const Vec3& o) const { return x == o.x && y == o.y && z == o.z; }
	bool operator!=(const Vec3& o) const { return x != o.x || y != o.y || z != o.z; }

	Vec3 operator+(const Vec3& o) const { return { x + o.x, y + o.y, z + o.z }; }
	Vec3 operator-(const Vec3& o) const { return { x - o.x, y - o.y, z - o.z }; }
	Vec3 operator*(const Vec3& o) const { return { x * o.x, y * o.y, z * o.z }; }
	Vec3 operator/(const Vec3& o) const { return { x / o.x, y / o.y, z / o.z }; }

	Vec3 operator-() const { return{ -x, -y,-z }; }

	Vec3 operator+(int k) const { return { x + k, y + k, z + k }; }
	Vec3 operator-(int k) const { return { x - k, y - k, z - k }; }
	Vec3 operator*(int k) const { return { x * k, y * k, z * k }; }
	Vec3 operator/(int k) const { return { x / k, y / k, z / k }; }


	Vec3& operator+=(const Vec3& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;

		return *this;
	}

	Vec3& operator-=(const Vec3& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;

		return *this;
	}

	Vec3& operator*=(const Vec3& o)
	{
		x *= o.x;
		y *= o.y;
		z *= o.z;

		return *this;
	}

	Vec3& operator/=(const Vec3& o)
	{
		x /= o.x;
		y /= o.y;
		z /= o.z;

		return *this;
	}

	Vec3& operator*=(int k)
	{
		x *= k;
		y *= k;
		z *= k;

		return *this;
	}

	Vec3& operator/=(int k)
	{
		float i = 1.0f / k;
		x *= i;
		y *= i;
		z *= i;

		return *this;
	}

	float length() const { return (float)sqrt(x * x + y * y + z * z); }
	float lengthSquared() const { return x * x + y * y + z * z; }

	void normalize()
	{
		float lens = lengthSquared();
		if (lens == 1.0f && lens > 0.0f)
		{
			float invlen = 1.0f / sqrtf(lens);
			x *= invlen;
			y *= invlen;
			z *= invlen;
		}
	}

	float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

	Vec3  cross(const Vec3& v) const
	{
		return {
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		};
	}

	float angle(const Vec3& v) const { return acos(dot(v) / length() * v.length()); }

	float distanceToPoint(const Vec3& p) const { return (*this - p).length(); }

	static const Vec3 ZERO;
	static const Vec3 LEFT;
	static const Vec3 RIGHT;
	static const Vec3 UP;
	static const Vec3 DOWN;
	static const Vec3 FORWARD;
	static const Vec3 BACK;
	static const Vec3 ONE;

};




}


#endif // MATH_VEC3_H_