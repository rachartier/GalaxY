#include "player.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rand.h"
#include "memory.h"
#include "menu.h"
#include "planet.h"
#include "drop.h"
#include "crew.h"

Player* player_create(void) {
	Player	*player = xmalloc(sizeof(Player));
	Staff	user;

	user = player_setByUser();

	player->power = 0u;

	crew_add_player(&player->ship.crew, user);

	ship_create(&player->ship, 0, 1);

	player->exp = 0;
	player->lvl = 50;

	player->money = 10000000.0f;
	player->planetIndex = 0;
	player->satelliteIndex = -1;
	player->stats.planetsVisited = 0;

    player->wantToExit = false;
    player->isDead = false;

	return player;
}

Staff	player_setByUser(void) {
	Staff	staff;
	Menu	*menu = menu_create();
	int		i = 0;
	char	name[32];
	int   cmd;

	menu_setTitle(menu, "Creation du personnage");
	menu_display(*menu);

	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");

	printf("Nom: ");

	fgets(name, 32, stdin);

	while (name[0] == ' ' || name[1] == '\n') {
		printf("Veuillez choisir un nom correct: ");
		fgets(name, 32, stdin);
	}

	for (; name[i] != '\n'; ++i)
		;

	name[i] = '\0';

	printf("\nRace:\n");
	printf("\t1) Humain\n");
	printf("\t2) Robot\n");
	printf("\t3) Alien\n");
	printf("\t4) Roc\n");
	printf("\t5) Intel\n");
	printf("\t6) Warbrog\n");

	cmd = menu_getcmd(*menu);
	while (cmd == 0) {
		printf("Entrez une classe valide\n");

		cmd = menu_getcmd(*menu);
	}

	staff = staff_create_user(name, (SpecieType)(cmd - 1));

	menu_destroy(menu);

	return staff;
}

void	player_destroy(Player *player) {
	starsys_destroy(player->actStarsystem);
	xfree(player);
}

void	player_setLife(Player *player, unsigned life, unsigned maxLife) {
	player->ship.hull.life.actual = life;
	player->ship.hull.life.max = maxLife;
}

void	player_setshield(Player *player, unsigned shield, unsigned maxshield) {
	player->ship.hull.life.actual = shield;
	player->ship.hull.life.max = maxshield;
}

void	player_setFuel(Player *player, unsigned fuel, unsigned maxFuel) {
	player->ship.hull.fuel.actual = fuel;

	if (player->ship.hull.fuel.actual > player->ship.hull.fuel.max)
		player->ship.hull.fuel.actual = player->ship.hull.fuel.max;

	player->ship.hull.fuel.max = maxFuel;
}

void	player_setFood(Player *player, unsigned food, unsigned maxFood) {
	player->ship.hull.food.actual = food;
    player->ship.hull.food.max = maxFood;
}

void	player_info(Player player) {
	printf("\t- Argent: %.3f$\n", player.money);
	printf("\t- Degats d'attaque: %u\n", player.power);
	printf("\t- Nombre de personne a bord: %u/%u\n", player.ship.crew.nStaff, player.ship.hull.nMaxStaff);
	printf("Nombre de planetes visitees: %d\n", player.stats.planetsVisited);

	hull_display(player.ship.hull);

	for (unsigned i = 0; i < player.ship.hull.nWeaponsSlot; ++i)
		weapon_display(player.ship.weapon[i]);

	armor_display(player.ship.armor);
	engine_display(player.ship.engine);
}

bool	player_isDead(Player *player) {
	return player->ship.hull.life.actual == 0;
}

float	player_getDistanceOfPlanet(Player player, Planet planet) {
	float dst = 0.f;
	dst = (float)fabs(planet.distanceOfNearestStar - player.actStarsystem->planet[player.planetIndex].distanceOfNearestStar);
	return dst;
}

void	player_set_planet(Player *player) {
	player->actPlanet = player->actStarsystem->planet[player->planetIndex];
	player->actStarsystem->planet[player->planetIndex].visited = true;

	player->stats.planetsVisited++;
	player->satelliteIndex = -1;

	if (player->actPlanet.isPortal)
		printf("\nVous arrivez a un %s\n", player->actPlanet.name);
	else
		printf("\nVous arrivez a la planete %s\n", player->actPlanet.name);

	planet_show_stats(player->actPlanet);
}

void	player_move_toPlanet(Player *player, int dir) {
	if (player->planetIndex + dir > 0 && player->planetIndex + dir < (int)player->actStarsystem->numberPlanets) {
		unsigned fuelCost = floor(player_getDistanceOfPlanet(*player, player->actStarsystem->planet[player->planetIndex + dir]));

        crew_need_eat(&player->ship.crew, &player->ship.hull.food.actual, &player->isDead);
        if(!player->isDead) {
	    	if (player->ship.hull.fuel.actual - fuelCost > 0) {
		    	player->planetIndex += dir;
		    	player_set_planet(player);

	    		if (player->actPlanet.type == P_TYPE_STAR)
	    			printf("\nVous etes deja dans le systeme planetaire\n");
	    		else if (dir == 0)
	    			printf("Vous revenez a la planete %s\n", player->actPlanet.name);
	    		else
	    			player->ship.hull.fuel.actual -= fuelCost;
	    	}
	    	else
	    		printf("Vous n'avez plus de carburant\n");
	    }
    }
	else
		printf("Vous ne pouvez pas allez plus loin\n\n");
}

void	player_move_toSatellite(Player *player) {
	if (player->satelliteIndex < (int)player->actPlanet.nSatellite) {
		player->actPlanet.satellite[player->satelliteIndex].visited = true;

		printf("Vous arrivez au satellite n%u de la planete %s\n", player->satelliteIndex + 1, player->actPlanet.name);
	}
}

void	player_move_toSystem(Player *player, StarSystem *starsystem) {
	player->planetIndex = 1;
	player->stats.planetsVisited--;
	player->actStarsystem = starsystem;
	player_set_planet(player);
}

void	player_drop(Player *player, Planet *planet) {
	if (!planet->isHabitable && (planet->type != P_TYPE_PORTAL_IN && planet->type != P_TYPE_PORTAL_OUT)) {
		if (!planet->searched) {
			planet->searched = true;
			if (CHANCE(5)) {
				printf("Vous trouvez un vaisseau...\n");

				drop_scrap(player);
				drop_fuel(player);
				drop_weapon(player);
				drop_staff(player);
			}
			else
				printf("Vous ne trouvez rien d'interessant\n");
		}
		else
			printf("Vous avez deja fouiller la planete\n");
	}
	else
		printf("Impossible de fouiller ici\n");
}

void	player_setItem(Player *player, ItemType iType, int id, void *item) {
	switch (iType) {
	case I_WEAPON:
	case I_ARMOR:
	case I_ENGINE:
	case I_HULL:
		ship_set_item(&player->ship, iType, id, item);
		break;

	case I_FOOD:
	{
		unsigned food = *(unsigned *)item;
		player->ship.hull.food.actual += food;
	}
	break;
	case I_FUEL:
	{
		unsigned fuel = *(unsigned *)item;
		player->ship.hull.fuel.actual += fuel;
	}
	break;
	default:
		break;
	}
}
