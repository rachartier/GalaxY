#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "command.h"
#include "planet.h"
#include "rand.h"
#include "starsystem.h"
#include "menu.h"
#include "memory.h"

void	set_seed(void) {
	Menu		*menu = menu_create();
	char		cmd = 1;
	bool		running = true;
	unsigned	seed;

	menu_setTitle(menu, "Seed");

	menu_addButtonText(menu, "Generer aleatoirement un seed");
	menu_addButtonText(menu, "Entrer un seed");

	while (running) {
		menu_display(*menu);
		cmd = menu_getcmd(*menu);

		switch (cmd) {
		case 'a': {
			seed = time(NULL) * clock();

			printf("Seed: %u\n\n", seed);

			running = false;
			break;
		}
		case 'b':
			running = false;
			printf("Entrez un seed: ");
			scanf("%u", &seed);
			break;
		default:
			running = false;
			break;
		}
		srand(seed);
	}
	purge_stdin();
}

void	play(void) {
	Player		*player = NULL;
	StarSystem	*sys = NULL;

	set_seed();

	player = player_create(100, 50, 80, 1000, 100, 100);
	sys = starsys_create();

	player_moveToSystem(player, sys);

	while (!player->wantToExit) {
		cmd_get(player);
	}

	player_destroy(player);
}

int main(void) {
	Menu		*mainMenu = menu_create();
	int			cmd = 1;

	menu_setTitle(mainMenu, "GalaxY (V0.0.0)");

	menu_addButtonText(mainMenu, "Jouer");
	menu_addButtonText(mainMenu, "Charger");
	menu_addButtonText(mainMenu, "Quitter");

	while (cmd != 0) {
		menu_display(*mainMenu);
		cmd = menu_getcmd(*mainMenu);
		switch (cmd) {
		case 'a':
			play();
			break;
		case 'b':
			break;
		case 'c':

			break;
		default:
			break;
		}
	}

	menu_destroy(mainMenu);

	return 0;
}