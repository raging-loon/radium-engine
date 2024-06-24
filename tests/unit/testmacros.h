#ifndef TESTS_UNIT_TEST_MACROS_H_
#define TESTS_UNIT_TEST_MACROS_H_

#define RUN_TEST_CASE(x) test_cases_failed += test_##x(); totalNumTests++;

#define BEGIN_TEST_CASE(x)\
int test_##x()\
{ \
const char* testname=#x;\

#define END_TEST_CASE() \
printf("\033[32mTest case %s succeeded\033[0m\n", testname);\
return 0;\
}

#define REQUIRE(x) {\
if(!(x))\
{\
printf("\033[31mTest Case \"%s\" (%s) failed!\033[0m\n", testname, #x); \
return 1;\
}\
}

#define GET_TEST_NAME(testname) run##testname

#define BEGIN_TEST_SUITE(testname) \
int radium_unittest::GET_TEST_NAME(testname)Tests() \
{\
printf("\033[34mStarting tests for %s\033[0m\n",#testname);\
int test_cases_failed =0;\
int totalNumTests = 0;


#define END_TEST_SUITE(testname)\
radium_unittest::g_totalUnitTests += totalNumTests;\
if(test_cases_failed == 0)\
printf("\033[32mAll tests cases for suite %s passed\033[0m\n",#testname);\
else\
 printf("\n\033[31m%d tests failed for test suite %s\033[0m\n", test_cases_failed, #testname);\
return test_cases_failed;\
}

#define DECLARE_TEST(x) int test_##x()


#endif // TESTS_UNIT_UNIT_TEST_H_