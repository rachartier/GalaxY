#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "starsystem.h"
#include "menu.h"
#include "player.h"
#include "command.h"
#include "memory.h"

void	set_seed(void) {
	Menu		*menu = menu_create();
	int      cmd = 1;
	bool		running = true;
	unsigned	seed = 42;

	menu_setTitle(menu, "Seed");

	menu_addButtonText(menu, "Generer aleatoirement un seed");
	menu_addButtonText(menu, "Entrer un seed");

	while (running) {
		menu_display(*menu);
		cmd = menu_getcmd(*menu);

		switch (cmd) {
		case 1: {
			seed = (unsigned)time(NULL) / clock();

			printf("Seed: %u\n", seed);

			running = false;
			break;
		}
		case 2:
			running = false;
			printf("Entrez un seed: ");
			scanf("%u", &seed);

			purge_stdin();
			break;
		default:
			running = false;
			break;
		}
		srand(seed);
	}
}

void	play(void) {
	Player		*player = NULL;
	StarSystem	*sys = NULL;

	set_seed();

	putchar('\n');

	player = player_create(100, 50, 80, 1000, 100, 100);
	sys = starsys_create();

	LINE(80, '-');

	player_move_toSystem(player, sys);

	while (!player->wantToExit) {
		cmd_get(player);
	}

	player_destroy(player);
}

int main(void) {
	Menu		*mainMenu = menu_create();
	int			cmd = 1;
	bool		exit = false;

	menu_setTitle(mainMenu, "GalaxY (V0.10.20)");

	menu_addButtonText(mainMenu, "Jouer");
	menu_addButtonText(mainMenu, "Charger");
	menu_addButtonText(mainMenu, "Quitter");

	while (!exit) {
		menu_display(*mainMenu);
		cmd = menu_getcmd(*mainMenu);
		switch (cmd) {
		case 1:
			play();
			break;
		case 2:
			break;
		case 3:
			exit = true;
			break;
		default:
			break;
		}
	}

	menu_destroy(mainMenu);

	return 0;
}