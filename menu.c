#include "menu.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "memory.h"

Menu*	menu_create(void) {
	Menu	*newMenu = xmalloc(sizeof(Menu));

	newMenu->endList = 0;

	return newMenu;
}

void	menu_destroy(Menu *menu) {
	xfree(menu);
}

char	menu_getcmd(Menu menu) {
	char c;

	printf("\n> ");

	scanf("%c", &c);
	putchar('\n');

	purge_stdin();

	c = (char)tolower((char)c);

	if (c >= 'a' && c < 'a' + (int)menu.endList)
		return c;
	return 0;
}

void	menu_setTitle(Menu *menu, char *str) {
	if (str != NULL)
		strcpy(menu->title, str);
}

void	menu_addButtonText(Menu *menu, const char *text) {
	if (menu->endList < MAX_ELEMENTS) {
		strcpy(menu->element[menu->endList].text, text);
		menu->element[menu->endList].isVisible = true;

		menu->endList++;
	}
}

void	menu_removeButtonText(Menu *menu, int bId) {
	if (bId >= 0 && bId < MAX_ELEMENTS) {
		menu->element[bId].isVisible = false;
	}
}

void	menu_display(Menu menu) {
	int			titleLenght = strlen(menu.title);
	unsigned	i;

	for (i = 0; i < 80; ++i)
		putchar('-');

	putchar('\n');

	for (i = 0; i < (unsigned)40 - titleLenght / 2; ++i)
		putchar(' ');

	printf("%s\n", menu.title);

	for (i = 0; i < menu.endList; ++i) {
		if (menu.element[i].isVisible)
			printf("%c> %s\n", 'a' + i, menu.element[i].text);
	}
}