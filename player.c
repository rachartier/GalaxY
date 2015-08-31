#include "player.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rand.h"
#include "memory.h"

Player* player_create(unsigned life, unsigned shield, float fuel, unsigned weight, unsigned food, unsigned power) {
	Player	*player = xmalloc(sizeof(Player));

#define SETOPT(a, b) (a.max = a.actual = b)
	SETOPT(player->life, life);
	SETOPT(player->fuel, fuel);
	SETOPT(player->weight, weight);
	SETOPT(player->food, food);
	SETOPT(player->shield, shield);
#undef SETOPT

	//player->seed = ;

	player->planetIndex = 0;
	player->satelliteIndex = -1;
	player->power = power;
	player->stats.planetsVisited = 0;
	player->wantToExit = false;

	return player;
}

void	player_destroy(Player *player) {
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
	printf("\t- Capacite: %u/%ukg\n", player.weight.actual, player.weight.max);
	printf("\t- Vie: %u/%u\n", player.life.actual, player.life.max);
	printf("\t- Degats d'attaque: %u\n", player.power);
	printf("\t- Armure: %u\n", player.shield.actual);
	printf("\t- Nombre de personne a bord: %u/%u\n", 0, 0);
	printf("Nombre de planetes visitees: %d\n", player.stats.planetsVisited);
}

bool	player_isDead(Player *player) {
	return player->life.actual == 0;
}

float	player_getDistanceOfPlanet(Player player, Planet planet) {
	float dst = 0;
	dst += (float)fabs(planet.distanceOfNearestStar - player.actStarsystem->planet[player.planetIndex].distanceOfNearestStar);
	return dst;
}

void	player_moveToPlanet(Player *player, int dir) {
	if (player->planetIndex >= 0 && player->planetIndex + dir < player->actStarsystem->numberPlanets) {
		player->planetIndex += dir;
		float fuelCost = player_getDistanceOfPlanet(*player, player->actStarsystem->planet[player->planetIndex]);

		if (player->fuel.actual - fuelCost > 0.f) {
			memcpy(&player->actPlanet, &player->actStarsystem->planet[player->planetIndex], sizeof(Planet));
			player->actStarsystem->planet[player->planetIndex].visited = true;

			if (player->actPlanet.type == P_TYPE_STAR)
				printf("Vous arrivez au systeme stellaire %s", player->actStarsystem->planet[player->planetIndex].name);
			else if (dir == 0)
				printf("Vous revenez a la planete %s", player->actPlanet.name);
			else {
				if (player->actPlanet.isPortal)
					printf("Vous arrivez a un %s", player->actPlanet.name);
				else
					printf("Vous arrivez a la planete %s", player->actPlanet.name);
				player->fuel.actual -= fuelCost;
			}
			player->stats.planetsVisited++;
			player->satelliteIndex = -1;
		}
		else
			printf("Vous n'avez plus de carburant");
	}
	else
		printf("Vous ne pouvez pas allez plus loins, tapez \"aller prochain systeme\"\n\n");
}

void	player_moveToSatellite(Player *player) {
	if (player->satelliteIndex < player->actPlanet.nSatellite) {
		player->actPlanet.satellite[player->satelliteIndex].visited = true;

		printf("Vous arrivez au satellite n%u de la planete %s\n", player->satelliteIndex + 1, player->actPlanet.name);
	}
}

void	player_moveToSystem(Player *player, StarSystem *starsystem) {
	player->planetIndex = 0;
	player->stats.planetsVisited--;
	player->actStarsystem = starsystem;

	player_moveToPlanet(player, 1);
}

void	player_drop(Player *player, Planet *planet) {
	if (planet->type == P_TYPE_TERRESRTIAL && !planet->isHabitable) {
		if (!planet->visited) {
			planet->visited = true;
			if (CHANCE(2)) {
				printf("Vous trouvez un vaisseau abandonne...\n");

				if (CHANCE(3)) {
					unsigned addmoney = rand_born(5, 20);

					printf("\t- Vous prenez %u scraps", addmoney);

					player->money += addmoney;
				}
				if (CHANCE(3)) {
					if (player->fuel.actual < player->fuel.max) {
						float fuel = (float)rand_born(5, 30) + rand_float(0.f, 1.f);

						printf("\t- Vous recuperez %.1f fuel", fuel);

						player_setFuel(player, player->fuel.actual + fuel, player->fuel.max);
					}
				}
				else
					printf("Vous ne trouvez rien d'interessant\n");
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