#ifndef __MENU_H_GUARD__
#define __MENU_H_GUARD__

#include <stdbool.h>

#include "screen.h"

#include <string.h>

#define MAX_ELEMENTS	128

struct s_menu {
	struct {
		char	text[64];
		bool	isVisible;
	} element[MAX_ELEMENTS];

	char	title[32];
	size_t	endList;
};

typedef struct s_menu Menu;

Menu*	menu_create(void);
void	menu_destroy(Menu *menu);

char	menu_getcmd(Menu menu);
void	menu_setTitle(Menu *menu, char *str);

void	menu_display(Menu menu);

void	menu_addButtonText(Menu *menu, const char *text);
void	menu_removeButtonText(Menu *menu, int bId);

#endif /* #ifndef __MENU_H_GUARD__ */