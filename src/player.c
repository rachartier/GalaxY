#include "player.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "rand.h"
#include "memory.h"
#include "menu.h"
#include "planet.h"
#include "drop.h"

Player* player_create(unsigned life, unsigned shield, float fuel, unsigned weight, unsigned food, unsigned power) {
	Player	*player = xmalloc(sizeof(Player));
	Staff	user;

	Weapon	w = weapon_create_rand(0);
	Armor	a = armor_create_rand(0);
	Hull	h = hull_create_rand(0);

	user = player_setByUser();

	player->power = 0u;

	crew_add_player(&player->crew, user);

	player_setItem(player, I_WEAPON, &w);
	player_setItem(player, I_ARMOR, &a);
	player_setItem(player, I_HULL, &h);

	player->exp = 0;
	player->lvl = 50;

	player->money = 1000u;
	player->planetIndex = 0;
	player->satelliteIndex = -1;
	player->stats.planetsVisited = 0;
	player->wantToExit = false;

	return player;
}

Staff	player_setByUser(void) {
	Staff	staff;
	Menu	*menu = menu_create();
	int		i = 0;
	char	name[32];
	char	c;

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
	while (name[0] == ' ') {
		printf("Veuillez choisir un nom correct: ");
		fgets(name, 32, stdin);
	}

	for (; name[i] != '\n'; ++i)
		;

	name[i] = '\0';

	printf("\nRace:\n");
	printf("\ta) Humain\n");
	printf("\tb) Robot\n");
	printf("\tc) Alien\n");
	printf("\td) Roc\n");
	printf("\te) Intel\n");
	printf("\tf) Warbrog\n");

	c = menu_getcmd(*menu);
	while (c == 0) {
		printf("Entrez une classe valide\n");

		c = menu_getcmd(*menu);
	}

	staff = staff_create_user(name, (SpecieType)(c - 'a'));

	menu_destroy(menu);

	return staff;
}

void	player_destroy(Player *player) {
	starsys_destroy(player->actStarsystem);
	xfree(player);
}

void	player_setLife(Player *player, unsigned life, unsigned maxLife) {
	player->hull.life.actual = life;
	player->hull.life.max = maxLife;
}

void	player_setshield(Player *player, unsigned shield, unsigned maxshield) {
	player->hull.life.actual = shield;
	player->hull.life.max = maxshield;
}

void	player_setFuel(Player *player, float fuel, float maxFuel) {
	player->hull.fuel.actual = fuel;

	if (player->hull.fuel.actual > player->hull.fuel.max)
		player->hull.fuel.actual = player->hull.fuel.max;

	player->hull.fuel.max = maxFuel;
}

void	player_setFood(Player *player, unsigned food, unsigned maxFood) {
	player->food.actual = food;
	player->food.max = maxFood;
}

void	player_info(Player player) {
	printf("\t- Scraps: %u\n", player.money);
	printf("\t- Degats d'attaque: %u\n", player.power);
	printf("\t- Nombre de personne a bord: %u/%u\n", player.crew.nStaff, player.hull.nMaxStaff);
	printf("Nombre de planetes visitees: %d\n", player.stats.planetsVisited);

	hull_display(player.hull);
	weapon_display(player.weapon);
	armor_display(player.armor);
}

bool	player_isDead(Player *player) {
	return player->hull.life.actual == 0;
}

float	player_getDistanceOfPlanet(Player player, Planet planet) {
	float dst = 0;
	dst += (float)fabs(planet.distanceOfNearestStar - player.actStarsystem->planet[player.planetIndex].distanceOfNearestStar);
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
	if (player->planetIndex + dir >= 0 && player->planetIndex + dir < (int)player->actStarsystem->numberPlanets) {
		player->planetIndex += dir;
		float fuelCost = player_getDistanceOfPlanet(*player, player->actStarsystem->planet[player->planetIndex]);

		if (player->hull.fuel.actual - fuelCost > 0.f) {
			player_set_planet(player);

			if (player->actPlanet.type == P_TYPE_STAR)
				printf("\nVous etes deja dans le systeme planetaire\n");
			else if (dir == 0)
				printf("Vous revenez a la planete %s\n", player->actPlanet.name);
			else {
				player->hull.fuel.actual -= fuelCost;
			}
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

				drop_staff(player);
				drop_scrap(player);
				drop_fuel(player);
				drop_weapon(player);
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
	{
		Weapon	w = *(Weapon *)item;
		player->weapon = w;
		player->power += w.damage;
	}
	break;
	case I_ARMOR:
		player->armor = *(Armor *)item;
		break;
	case I_ENGINE:
		player->engine = *(Engine *)item;
		break;
	case I_HULL:
		player->hull = *(Hull *)item;
		break;
	default:
		break;
	}
}
