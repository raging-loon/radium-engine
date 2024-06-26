#include "math/math.h"
#include "test.h"
#include "testmacros.h"
#include <cstdio>
using namespace radium::math;

BEGIN_TEST_SUITE(Math)

	printf("\n\033[44mRunning Vector tests...\033[0m\n");
	RUN_TEST(Vec3(1, 2, 3) == Vec3(1, 2, 3));
	RUN_TEST(Vec3(1, 2, 3) != Vec3(3,2,1));
	
	RUN_TEST(Vec3(1, 2, 3) + Vec3(1, 2, 3) == Vec3(1, 2, 3) * 2);
	RUN_TEST(Vec3(1, 2, 3) - Vec3(1, 2, 3) == Vec3::ZERO);
	RUN_TEST(Vec3(1, 2, 3) * Vec3(1, 2, 3) == Vec3(1, 4, 9));

	RUN_TEST(Vec3(1,1,1) - 1 == Vec3::ZERO);
	RUN_TEST(Vec3(1, 2, 3) + 10 == Vec3(11, 12, 13));
	RUN_TEST(Vec3(1, 2, 3) / 10 == Vec3(1.0f / 10, 2.0f / 10, 3.0f / 10));
	RUN_TEST(Vec3(1,2,3) * 10 == Vec3(10, 20, 30));


END_TEST_SUITE(Math)

