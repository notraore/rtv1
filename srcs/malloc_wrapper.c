#include <stdlib.h>

#include <stdio.h>

void *malloc_wrapper(size_t size)
{
	void *new;
	static size_t count = 0;

	++count;
	printf("count:%zu\n", count);
	if (count > 2)
		return (NULL);
	new = malloc(size);
	return (new);
}