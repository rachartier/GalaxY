#ifndef __MENU_H__
#define __MENU_H__

#include <stdbool.h>
#include <string.h>

#define MAX_ELEMENTS	128

typedef struct s_menu {
	struct {
		char	text[64];
		bool	isVisible;
	} element[MAX_ELEMENTS];

	char	title[32];
	size_t	endList;
} Menu;

//typedef struct s_menu Menu;

Menu*	menu_create(void);
void	menu_destroy(Menu *menu);

int menu_getcmd(Menu menu);
void	menu_setTitle(Menu *menu, char *str);

void	menu_display(Menu menu);

void	menu_addButtonText(Menu *menu, const char *text);
void	menu_removeButtonText(Menu *menu, int bId);

#endif // __MENU_H__