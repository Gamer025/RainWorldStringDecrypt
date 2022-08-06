#include <stdlib.h>

void* xmalloc(int size)
{
	void* memory = malloc(size);

	if (!memory)
	{
		perror("memory alloc fails");
		exit(1);
	}
	return memory;
}