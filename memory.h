#ifndef __MEMORY_GUARD_H__
#define __MEMORY_GUARD_H__

#include <stdint.h>

void	xalloc_fail(void);
void*	xmalloc(size_t size);
void	xfree(void *memory);
void	purge_stdin(void);

#endif /* __MEMORY_GUARD_H__ */