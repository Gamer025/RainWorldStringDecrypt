#include <stdlib.h>
#include <stdio.h>

void* xmalloc(int size)
{
	void* memory = malloc(size);

	if (!memory)
	{
		fputs("memory alloc fails", stderr);
		exit(1);
	}
	return memory;
}