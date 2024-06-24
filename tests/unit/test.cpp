#include "test.h"

#ifdef RAD_ENABLE_TESTS

int radium_unittest::g_totalUnitTests = 0;

int radium_unittest::runTests(uint32_t test)
{
	g_totalUnitTests = 0;
	int failedTests = 0;
	if (test & TEST_CONFIG)
		failedTests += runConfigTests();

	return failedTests;
}


#endif // RAD_ENABLE_TESTS