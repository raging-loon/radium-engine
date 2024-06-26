#ifndef TESTS_UNIT_TEST_H_
#define TESTS_UNIT_TEST_H_
#define RAD_ENABLE_TESTS
#ifdef RAD_ENABLE_TESTS

#include "core/config/Config.h"
#include <cstdint>

namespace radium_unittest
{

extern int g_totalUnitTests;

constexpr unsigned int TEST_ALL		= 0xFF;
constexpr unsigned int TEST_CONFIG  = (1 << 0);
constexpr unsigned int TEST_MATH	= (1 << 1);

int runTests(uint32_t);

int runMathTests();
int runConfigTests();

} // radium_unittest

#endif // RAD_ENABLE_TESTS

#endif // TESTS_UNIT_TEST_H_