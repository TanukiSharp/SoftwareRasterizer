#include <stdio.h>
#include <stdlib.h>
#include "rasterizer.h"

char* read_file(char* filename)
{
	FILE* fd;
	long file_size;
	char* file_buffer;

	if (fopen_s(&fd, filename, "rb") != 0 || fd == NULL)
	{
		printf("Failed to open file '%s'.\n", filename);
		return NULL;
	}

	if (fseek(fd, 0, SEEK_END) != 0)
	{
		printf("Failed to seek end of file.\n");
		return NULL;
	}

	file_size = ftell(fd);

	if (file_size < 0L)
	{
		printf("Failed to query file size.\n");
		return NULL;
	}

	if (fseek(fd, 0, SEEK_SET) != 0)
	{
		printf("Failed to seek end of file.\n");
		return NULL;
	}

	file_buffer = (char*)malloc((size_t)file_size + 1);

	if (file_buffer == NULL)
	{
		malloc_error(file_size);
		return NULL;
	}

	if (fread(file_buffer, sizeof(char), file_size, fd) != file_size)
	{
		free(file_buffer);
		printf("Failed to read %ld bytes from file '%s'.\n", file_size, filename);
		return NULL;
	}

    file_buffer[file_size] = 0;

	return file_buffer;
}
