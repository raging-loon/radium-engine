#include "filesystem.h"
#include "core/debug/Log.h"
// Windows has a version of stat too
#include <sys/stat.h>

using radium::filesystem::File;

File::File(const char* path, const char* access)
	: fp(nullptr), m_isOpen(false)
{
	open(path, access);
}

File::~File()
{
	if(fp && m_isOpen)
		fclose(fp)
}

int File::open(const char* path, const char* access)
{
	if (m_isOpen)
		return -1;

	fp = fopen(path, access);

	if (!fp)
	{
		RAD_ENGINE_ERROR("Failed to open file at {}", path);
		return -1;
	}

	m_isOpen = true;
	return 0;
}

void File::close()
{
	if (fp)
	{
		fclose(fp);
		m_isOpen = false;
	}
}

int File::read(void* out, size_t size)
{
	assert(fp);
	return fread(out, 1, size, fp);
}

int File::write(void* in, size_t size)
{
	assert(fp);
	return fwrite(in, 1, size, fp);
}


int File::size()
{
	if (!m_isOpen)
		return -1;

	int curPos = ftell(fp);

	fseek(fp, 0, SEEK_END);
	int endPos = ftell(fp);

	rewind(fp);
	int begPos = ftell(fp);
	
	fseek(fp, begPos, SEEK_SET);

	assert(ftell(fp) == curPos);

	return (endPos - begPos);

	
}