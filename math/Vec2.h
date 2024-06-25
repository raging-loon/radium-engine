#ifndef MATH_VEC2_H_
#define MATH_VEC2_H_

#include <cmath>

namespace radium::math
{

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0), y(0) {}

	Vec2(float _x, float _y) : x(_x), y(_y) {}

	bool operator==(const Vec2& v) { return x == v.x && y == v.y; }
	bool operator!=(const Vec2& v) { return x != v.x || y != v.y; }


	Vec2 operator+(const Vec2& v) const { return { x + v.x, y + v.y }; }
	Vec2 operator-(const Vec2& v) const { return { x - v.x, y - v.y }; }
	Vec2 operator*(const Vec2& v) const { return { x * v.x, y * v.y }; }
	Vec2 operator/(const Vec2& v) const { return { x / v.x, y / v.y }; }

	Vec2 operator-() const { return{ -x, -y }; }

	Vec2 operator+(int k) const { return { x + k, y + k}; }
	Vec2 operator-(int k) const { return { x - k, y - k}; }
	Vec2 operator*(int k) const { return { x * k, y * k}; }
	Vec2 operator/(int k) const { return { x / k, y / k}; }



	Vec2& operator+=(const Vec2& o)
	{
		x += o.x;
		y += o.y;

		return *this;
	}

	Vec2& operator-=(const Vec2& o)
	{
		x -= o.x;
		y -= o.y;

		return *this;
	}

	Vec2& operator*=(const Vec2& o)
	{
		x *= o.x;
		y *= o.y;

		return *this;
	}

	Vec2& operator/=(const Vec2& o)
	{
		x /= o.x;
		y /= o.y;

		return *this;
	}

	Vec2& operator*=(int k)
	{
		x *= k;
		y *= k;

		return *this;
	}

	Vec2& operator/=(int k)
	{
		float i = 1.0f / k;
		x *= i;
		y *= i;

		return *this;
	}

	float length() const { return (float)sqrtf(x * x + y * y); }
	float lengthSquared() const { return x * x + y * y; }

	void normalize()
	{

		float lenSq = lengthSquared();
	
		if (!lenSq == 1.0f && lenSq > 0.0f)
		{
			float inv = 1.0 / lenSq;

			x *= inv;
			y *= inv;
		
		}
	}

	float dot(const Vec2& v) const { return x * v.x + y * v.y; }

	static const Vec2 RIGHT;
	static const Vec2 ZERO;
	static const Vec2 LEFT;
	static const Vec2 LEFT;
	static const Vec2 DOWN;
	static const Vec2 ONE;
	static const Vec2 UP;

};

}


#endif // MATH_VEC2_H_