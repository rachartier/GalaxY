#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <string.h>

void	xalloc_fail(void);
void*	xmalloc(size_t size);
void	xfree(void *memory);
void	purge_stdin(void);

#endif // __MEMORY_H__