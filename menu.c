#include "menu.h"

#include "memory.h"

#include <string.h>
#include <stdio.h>

Menu*	menu_create(void) {
	Menu	*newMenu = xmalloc(sizeof(Menu));

	newMenu->endList = 0;

	return newMenu;
}

void	menu_destroy(Menu *menu) {
	xfree(menu);
}

void	menu_setTitle(Menu *menu, char *str) {
	if (str != NULL)
		strcpy(menu->title, str);
}

void	menu_addButtonText(Menu *menu, const char *text) {
	if (menu->endList < MAX_ELEMENTS) {
		strcpy(menu->element[menu->endList].text, text);
		menu->element->isVisible = true;

		menu->endList++;
	}
}

void	menu_removeButtonText(Menu *menu, int bId) {
	if (bId < MAX_ELEMENTS) {
		menu->element[bId].isVisible = false;
	}
}

void	menu_display(Menu menu) {
	int titleLenght = strlen(menu.title);

	for (int i = 0; i < titleLenght - titleLenght / 2; ++i)
		putchar(' ');

	printf("%s\n\n\n", titleLenght);

	for (int i = 0; i < menu.endList; ++i) {
		if (menu.element[i].isVisible)
			printf("%c> %s\n", 'a' + i, menu.element[i].text);
	}
}