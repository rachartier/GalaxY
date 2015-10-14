#pragma once

#include <string.h>

void	xalloc_fail(void);
void*	xmalloc(size_t size);
void	xfree(void *memory);
void	purge_stdin(void);
