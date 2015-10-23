#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void	xalloc_fail(void) {
	fprintf(stderr, "[ERROR] Memory exhausted");
	exit(-1);
}

void*	xmalloc(size_t size) {
	void	*ptr = NULL;

	if (size != 0)
		ptr = malloc(size);

	assert(ptr != NULL);

	if (ptr == NULL)
		xalloc_fail();
	return ptr;
}

void	xfree(void *memory) {
	assert(memory != NULL);

	if (memory != NULL) {
		free(memory);
		memory = NULL;
	}
}

void	purge_stdin(void) {
	int c = 0;
	while ((c = getchar()) != '\n' && c != EOF);
}