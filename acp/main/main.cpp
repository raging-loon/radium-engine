#include <cstdio>
#include <string>
#include <spdlog/spdlog.h>
#include "mesh/MeshExporter.h"
int main(int argc, char** argv)
{

	if (argc != 3)
	{
		printf("Usage: acp.exe <source> <dest>");
		return 1;
	}


	std::string source = argv[1];
	std::string dest = argv[2];

	acp::MeshExporter exp(source);
	exp.process();
	exp.serialize(dest);


	return 0;
}