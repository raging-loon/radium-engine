#ifndef DRIVERS_FILE_SYSTEM_FILE_SYSTEM_H_
#define DRIVERS_FILE_SYSTEM_FILE_SYSTEM_H_

#include <cstdio>
namespace radium::filesystem
{

class File
{
public:
	File(const char* path, const char* access);


	virtual int open(const char* path, const char* access);
	virtual void close();

	virtual inline bool isOpen() { return m_isOpen; }

	virtual int read(void* out, size_t size);
	virtual int write(void* in, size_t size);
	virtual int size();

private:

	FILE* fp;
	bool m_isOpen;
	char path[];
};



} // radium::filesystem



#endif // DRIVERS_FILE_SYSTEM_FILE_SYSTEM_H_