#include "core/config/Config.h"
#include "core/Variant.h"
#include "core/debug/Log.h"

#include <stdio.h>

#ifdef RAD_PLATFORM_WIN32
# include <Windows.h>
#endif //RAD_PLATFORM_WIN32

using radium::Config;
using radium::Variant;



static bool isInteger(const char* s)
{
	while (*s)
	{
		if (!((*s >= 0x30 && *s <= 0x39) || *s == '-'))
			return false;
		s++;
	}

	return true;
}


Config::Config()
{

}

Config::~Config()
{

}

Variant& Config::operator[](std::string k)
{
	return m_kvcfgmap[k];
}



bool Config::loadConfig(const char* filename )
{
	if (!filename)
		filename = "engine.ini";

	// TODO: MOVE THIS TO THE FILSYSTEM ABSTRACTION
	FILE* fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);

	RAD_ENGINE_INFO("Loading config file at {} ({} bytes)", filename, filesize);
	rewind(fp);
	if (!fp)
	{
		RAD_ENGINE_CRITICAL("Failed to open config file at {}", filename);
		return false;
	}

	char* filebuffer = new char[filesize];

	fread(filebuffer, 1, filesize, fp);

	bool res = readConfig(filebuffer, filesize);

	fclose(fp);
	delete[] filebuffer;

	return res;
}


bool Config::readConfig(char* cfgBuf, size_t sz)
{
	assert(cfgBuf && sz > 0);
	// config lines shouldn't be more than 64 characters
	char line[256];
	memset(line, 0, sizeof(line));

	int curlinelen = 0;

	bool shouldSkip = false;

	for( int cread = 0; cread < sz; cread++)
	{
		char cur = cfgBuf[cread];
		if (shouldSkip && cur != '\n')
			continue;

		// skip comments, section indicators, and blank lines
		if (cur == '#' || cur == '[')
			shouldSkip = true;
		else if (cur == '\n')
		{
			if (shouldSkip) shouldSkip = false;
			if (curlinelen == 0) continue;
			else
			{
				line[curlinelen + 1] = 0;
				if (!parseLine(line))
					return false;
				curlinelen = 0;
			}
		}
		else
		{
			if (!shouldSkip)
				line[curlinelen++] = cur;
		}



	}



	return true;
}

bool Config::parseLine(char* line)
{
	assert(line);

	char key[64] = { 0 };
	char* val = nullptr;
	int keylen = 0;

	while (*line)
	{
		if (*line == '=')
		{
			val = line + 1;
			break;
		}
		else
			key[keylen++] = *line;
		line++;
	}

	if (!val)
		return false;

	key[keylen] = 0;

	auto& rval = m_kvcfgmap[key];

	if (strcmp(val, "true") == 0)
		rval = true;

	else if (strcmp(val, "false") == 0)
		rval = false;

	else if (isInteger(val))
		rval = atoi(val);
	else
	{
		RAD_ENGINE_ERROR("Cannot deduce type for value {}", val);
		return false;
	}



	return true;
}
