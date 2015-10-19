#include "screen.h"
#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

Screen* screen_create(void) {
	Screen	*screen = xmalloc(sizeof(Screen));

	screen->actualRow = 0;
	screen->actualCol = 0;

	screen_clear(screen);

	return screen;
}

void	screen_destroy(Screen *screen) {
	xfree(screen);
}

void	screen_display(Screen screen) {
	for (int y = 0; y < CON_HEIGHT; ++y) {
		for (int x = 0; x < CON_WIDTH; ++x) {
			putchar(screen.buffer[x][y]);
		}
		putchar('\n');
	}
}

void	screen_clear(Screen *screen) {
	for (int y = 0; y < CON_HEIGHT; ++y) {
		for (int x = 0; x < CON_WIDTH; ++x) {
			screen->buffer[x][y] = ' ';
		}
	}
}

void	screen_addchar(Screen *screen, char c) {
	screen_addcharat(screen, screen->actualCol, screen->actualRow, c);
}

void	screen_addtext(Screen *screen, char *text) {
	screen_addtextat(screen, screen->actualCol, screen->actualRow, text);
}

void	screen_addcharat(Screen *screen, int x, int y, char c) {
	screen->actualCol = x;
	screen->actualRow = y;

	if (x >= CON_WIDTH) {
		screen->actualCol = 0;
		screen->actualRow++;
	}

	screen->buffer[x][y] = c;
	screen->actualCol++;
}

void	screen_addtextat(Screen *screen, int x, int y, char *text) {
	if (text != NULL) {
		size_t textLenght = strlen(text);

		screen->actualCol = x;
		screen->actualRow = y;

		for (int i = 0; i < (int)textLenght; ++i) {
			char c = text[i];

			if (c != '\n') {
				screen_addcharat(screen, screen->actualCol, screen->actualRow, c);
			}
			else {
				screen->actualCol = 0;
				screen->actualRow++;
			}
		}
	}
}