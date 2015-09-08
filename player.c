#include "player.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rand.h"
#include "memory.h"
#include "menu.h"
#include "planet.h"

Player* player_create(unsigned life, unsigned shield, float fuel, unsigned weight, unsigned food, unsigned power) {
	Player	*player = xmalloc(sizeof(Player));
	Staff	user;

	user = player_setByUser();

	crew_add_player(&player->crew, user);

	player->exp = 0;
	player->lvl = 50;

#define SETOPT(a, b) (a.max = a.actual = b)
	SETOPT(player->life, life);
	SETOPT(player->fuel, fuel);
	SETOPT(player->weight, weight);
	SETOPT(player->food, food);
	SETOPT(player->shield, shield);
#undef SETOPT

	player->money = 1000;
	player->planetIndex = 0;
	player->satelliteIndex = -1;
	player->power = power;
	player->stats.planetsVisited = 0;
	player->wantToExit = false;

	return player;
}

Staff	player_setByUser(void) {
	Staff	staff;
	Menu	*menu = menu_create();
	char	name[32];

	char	c;

	menu_setTitle(menu, "Creation du personnage");
	menu_display(*menu);

	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");
	menu_addButtonText(menu, "");

	printf("Nom: ");

	fgets(name, 32, stdin);
	while (name[0] == ' ') {
		printf("Veuillez choisir un nom correct: ");
		fgets(name, 32, stdin);
	}

	printf("\nRace:\n");
	printf("\ta) Humain\n");
	printf("\tb) Robot\n");
	printf("\tc) Alien\n");
	printf("\td) Roc\n");

	c = menu_getcmd(*menu);
	while (c == 0) {
		printf("Entrez une classe valide\n");

		c = menu_getcmd(*menu);
	}

	staff = staff_create_user(name, (specie)(c - 'a'));

	menu_destroy(menu);

	return staff;
}

void	player_destroy(Player *player) {
	starsys_destroy(player->actStarsystem);
	xfree(player);
}

void	player_setLife(Player *player, unsigned life, unsigned maxLife) {
	player->life.actual = life;
	player->life.max = maxLife;
}

void	player_setshield(Player *player, unsigned shield, unsigned maxshield) {
	player->life.actual = shield;
	player->life.max = maxshield;
}

void	player_setFuel(Player *player, float fuel, float maxFuel) {
	player->fuel.actual = fuel;

	if (player->fuel.actual > player->fuel.max)
		player->fuel.actual = player->fuel.max;

	player->fuel.max = maxFuel;
}

void	player_setWeight(Player *player, unsigned weight, unsigned maxWeight) {
	player->weight.actual = weight;
	player->weight.max = maxWeight;
}

void	player_setFood(Player *player, unsigned food, unsigned maxFood) {
	player->food.actual = food;
	player->food.max = maxFood;
}

void	player_info(Player player) {
	printf("\t- Fuel: %.1f/%.1f\n", player.fuel.actual, player.fuel.max);
	printf("\t- Scraps: %u\n", player.money);
	printf("\t- Capacite: %u/%ukg\n", player.weight.actual, player.weight.max);
	printf("\t- Vie: %u/%u\n", player.life.actual, player.life.max);
	printf("\t- Degats d'attaque: %u\n", player.power);
	printf("\t- Armure: %u\n", player.shield.actual);
	printf("\t- Nombre de personne a bord: %u/%u\n", 0, 0);
	printf("Nombre de planetes visitees: %d\n", player.stats.planetsVisited);

	crew_display(player.crew);
}

bool	player_isDead(Player *player) {
	return player->life.actual == 0;
}

float	player_getDistanceOfPlanet(Player player, Planet planet) {
	float dst = 0;
	dst += (float)fabs(planet.distanceOfNearestStar - player.actStarsystem->planet[player.planetIndex].distanceOfNearestStar);
	return dst;
}

void	player_move_toPlanet(Player *player, int dir) {
	if (player->planetIndex + dir >= 0 && player->planetIndex + dir < (int)player->actStarsystem->numberPlanets) {
		player->planetIndex += dir;
		float fuelCost = player_getDistanceOfPlanet(*player, player->actStarsystem->planet[player->planetIndex]);

		if (player->fuel.actual - fuelCost > 0.f) {
			memcpy(&player->actPlanet, &player->actStarsystem->planet[player->planetIndex], sizeof(Planet));
			player->actStarsystem->planet[player->planetIndex].visited = true;

			if (player->actPlanet.type == P_TYPE_STAR)
				printf("\nVous etes dans le systeme stellaire\n");
			else if (dir == 0)
				printf("Vous revenez a la planete %s\n", player->actPlanet.name);
			else {
				if (player->actPlanet.isPortal)
					printf("Vous arrivez a un %s\n", player->actPlanet.name);
				else
					printf("Vous arrivez a la planete %s\n", player->actPlanet.name);
				player->fuel.actual -= fuelCost;
			}
			player->stats.planetsVisited++;
			player->satelliteIndex = -1;

			planet_show_stats(player->actPlanet);
		}
		else
			printf("Vous n'avez plus de carburant\n");
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
	player->planetIndex = 0;
	player->stats.planetsVisited--;
	player->actStarsystem = starsystem;

	player_move_toPlanet(player, 1);
}

void	player_drop(Player *player, Planet *planet) {
	if (!planet->isHabitable && (planet->type != P_TYPE_PORTAL_IN && planet->type != P_TYPE_PORTAL_OUT)) {
		if (!planet->visited) {
			planet->visited = true;
			if (CHANCE(2)) {
				printf("Vous trouvez un vaisseau...\n");

				if (CHANCE(3)) {
					unsigned addmoney = rand_born(5, 20);

					printf("\t- Vous prenez %u scraps\n", addmoney);

					player->money += addmoney;
				}
				if (CHANCE(3)) {
					if (player->fuel.actual < player->fuel.max) {
						float fuel = rand_float(10.f, 30.f);

						printf("\t- Vous recuperez %.1f fuel\n", fuel);

						player_setFuel(player, player->fuel.actual + fuel, player->fuel.max);
					}
				}
				if (CHANCE(8)) {
					Staff staff = staff_create();
					char  c;

					printf("Vous trouvez un membre du vaisseau: ");

					staff_set_life(&staff, rand_born(10, 80));

					staff_display(staff);

					printf("Voulez vous le recruter [o/n]?");
					scanf("%c", &c);

					if (c == 'o') {
						crew_add_staff(&player->crew, staff);
					}
				}
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

void	player_setItem(Player *player, ItemType iType, void *item) {
	switch (iType) {
	case I_WEAPON:
		//	player
		break;
	case I_ARMOR:
		//commerce->armor[id] = *(Armor *)item;
		break;
	case I_ENGINE:

		break;
	case I_HULL:

		break;
	default:
		break;
	}
}