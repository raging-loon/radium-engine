#include "test.h"
#include "testmacros.h"

DECLARE_TEST(test1);

//int radium_unittest::runConfigTests()
//{
//
//	BEGIN_TEST(config)
//		RUN_TEST_CASE(test1);
//	END_TEST(config)
//	return 0;
//}

BEGIN_TEST_SUITE(Config)
	RUN_TEST_CASE(test1);
END_TEST_SUITE(Config)


BEGIN_TEST_CASE(test1)
REQUIRE(1 != 1);
END_TEST_CASE()
