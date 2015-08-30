#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "command.h"
#include "planet.h"
#include "rand.h"
#include "starsystem.h"
#include "menu.h"

int main(void) {
	Player		*player = NULL;
	StarSystem	*sys = NULL;

	Menu		*mainMenu = menu_create();

	menu_setTitle(mainMenu, "GalaxY (V0.0.0)");

	player = player_create(100, 50, 80, 1000, 100, 100);

	//menu_display(*mainMenu);

	//printf("")

	srand(time(NULL));

	sys = starsys_create();
	player_moveToSystem(player, sys);

	while (!player->wantToExit) {
		cmd_get(player);
	}

	player_destroy(player);
	menu_destroy(mainMenu);
	return 0;
}