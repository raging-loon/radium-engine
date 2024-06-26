#include "vec3.h"

namespace radium::math
{

	const Vec3 Vec3::ZERO		(0.0f,0.0f,0.0f);
	const Vec3 Vec3::LEFT		(-1.0f, 0.0f, 0.0f);
	const Vec3 Vec3::RIGHT		(1.0f, 0.0f, 0.0f);
	const Vec3 Vec3::UP			(0.0f, 1.0f, 0.0f);
	const Vec3 Vec3::DOWN		(0.0f, -1.0f, 0.0f);
	const Vec3 Vec3::FORWARD	(0.0f, 0.0f, 1.0f);
	const Vec3 Vec3::BACK		(0.0f, 0.0f, -1.0f);
	const Vec3 Vec3::ONE		(1.0f, 1.0f, 1.0f);
}