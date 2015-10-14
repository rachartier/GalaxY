#ifndef __SCREEN_H_GUARD__
#define __SCREEN_H_GUARD__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Taille standard de la console
#define CON_WIDTH	79
#define CON_HEIGHT	24

struct s_screen {
	char	buffer[CON_WIDTH][CON_HEIGHT];

	int		actualRow;
	int		actualCol;
};

typedef struct s_screen Screen;

Screen* screen_create(void);
void	screen_destroy(Screen *screen);

void	screen_display(Screen screen);
void	screen_clear(Screen *screen);

void	screen_addchar(Screen *screen, char c);
void	screen_addtext(Screen *screen, char *text);

void	screen_addcharat(Screen *screen, int x, int y, char c);
void	screen_addtextat(Screen *screen, int x, int y, char *text);

#endif /* __SCREEN_H_GUARD__ */
