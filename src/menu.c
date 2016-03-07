#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "util.h"
#include "memory.h"

Menu*	menu_create(void) {
	Menu	*newMenu = xmalloc(sizeof(Menu));

	newMenu->endList = 0;

	return newMenu;
}

void	menu_destroy(Menu *menu) {
	xfree(menu);
}

int menu_getcmd(Menu menu) {
	char 	str[32] = {'\0'};
	int 	res;
	bool 	good = false;

	do {
		printf("\n> ");

		fgets(str, 8, stdin);

		for(int j = 0; str[j] != '\0'; ++j) {
			if(!isdigit(str[j])) {
				good = false;
				break;
			}
			else if(str[j] == '\n') {
				str[j] = '\0';
			}
			else {
				good = true;
			}
		}
		res = atoi(str);

	} while ((res < 1 || res >= 1 + (int)menu.endList) && !good);


	return res;
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

void	menu_display_header(const char *title) {
	int	titleLenght = strlen(title);

	LINE(80, '-');
	putchar('\n');
	LINE(40 - titleLenght / 2, ' ');

	printf("%s\n", title);
}

void	menu_display(Menu menu) {
	unsigned	i;

	menu_display_header(menu.title);

	for (i = 0; i < menu.endList; ++i) {
		if (menu.element[i].isVisible)
			printf("%d> %s\n", i + 1, menu.element[i].text);
	}
}
