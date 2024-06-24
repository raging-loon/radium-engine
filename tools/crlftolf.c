#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage: ./crlftolf <file>\n");
		return 1;
	}


	size_t filesize = 0;
	FILE* fp = fopen(argv[1], "r");
	
	if (!fp)
	{
		perror("Could not open file!");
		return 0;
	}
	
	fseek(fp, 0L, SEEK_END);
	filesize = ftell(fp);
	rewind(fp);

	// could probably optimize this to only use one buffer
	unsigned char* buffer = (unsigned char*)malloc(sizeof(char) * filesize + 1);
	unsigned char* outbuffer = (unsigned char*)malloc(sizeof(char) * filesize + 1);

	memset(outbuffer, 0, filesize + 1);
	fread(buffer, 1, filesize, fp);
	buffer[filesize + 1] = 0;
	
	fclose(fp);

	size_t outbuflen = 0;

	for (int i = 0; i <= filesize; i++)
	{
		if (buffer[i] != '\x0d')
			outbuffer[outbuflen++] = buffer[i];
	}


	FILE* out = fopen(argv[1], "w");

	if (fp)
	{
		fwrite(outbuffer, 1, outbuflen, out);
		fclose(out);
	}
	else
		perror("Could not open file for writing!");

	free(buffer);
	free(outbuffer);

	return 0;
}