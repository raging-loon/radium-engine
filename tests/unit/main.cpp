#include <cstdio>
#include <cstdint>
#include <cassert>
#include "test.h"

#ifdef RAD_PLATFORM_WIN32
# include <windows.h>
#endif // RAD_PLATFORM_WIN32

static void printHelp();
// parse list of params e.g. all, math
static uint16_t parseTestParams(const char* params);
// parse single param e.g. all
static uint16_t parseTestParam(const char* param);


int main(int argc, char** argv)
{
	printf("Radium Engine - Unit Tests\n");

	if (argc != 2)
	{
		printHelp();
		return 1;
	}

#ifdef RAD_PLATFORM_WIN32
	// enable colors on windows
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(handle, &consoleMode);
	SetConsoleMode(handle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif // RAD_PLATFORM_WIN32


	uint16_t testParams = parseTestParams(argv[1]);

	int failedTests = radium_unittest::runTests(testParams);
	
	if (failedTests != 0)
		printf("\n\033[31m%d out of %d tests failed\033[0m\n", failedTests, radium_unittest::g_totalUnitTests);
	else
		printf("\n\033[32mAll %d tests passed :)\033[0m\n", radium_unittest::g_totalUnitTests);
	
	return failedTests;
}

uint16_t parseTestParams(const char* params)
{
	char curTest[256] = { 0 };
	int ctlen = 0;

	int len = strlen(params);
		
	uint16_t testsEnabled = 0;

	for(int i = 0; i <= len; i++)
	{
		char cur = params[i];

		if (cur == ',' || cur == '\0')
		{
			curTest[ctlen + 1] = 0;
			

			testsEnabled |= parseTestParam(curTest);

			memset(curTest, 0, ctlen);
			ctlen = 0;
		}
		else
		{
			curTest[ctlen++] = cur;
		}

	}

	return testsEnabled;

}
uint16_t parseTestParam(const char* param)
{
	assert(param);

	if (strcmp(param, "all") == 0)
		return radium_unittest::TEST_ALL;
	if (strcmp(param, "config") == 0)
		return radium_unittest::TEST_CONFIG;
	if (strcmp(param, "math") == 0)
		return radium_unittest::TEST_MATH;
	else
		printf("Unknown Test Parameter: %s\n", param);
	return 0;

}

void printHelp()
{
	printf("Usage: ./radium-engine <tests>\n");
	printf("\nTests:\n");
	printf(	"\tall - Run all tests\n"
			"\tconfig - Run Configuration tests\n"
			"\tmath - Run math test\n"			
	);
}