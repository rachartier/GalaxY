#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdbool.h>
#include <string.h>

#include "crew.h"
#include "starsystem.h"
#include "market.h"
#include "planet.h"
#include "util.h"

typedef struct s_player {
	Planet		actPlanet;
	StarSystem	*actStarsystem;

	Crew		crew;

	Weapon		weapon;
	Armor		armor;
	Engine		engine;
	Hull		hull;

	OptionUnsigned	food;

	float	 money;

	unsigned power;
	unsigned seed;

	unsigned exp;
	unsigned lvl;

	int		planetIndex;
	int		satelliteIndex;

	struct {
		int planetsVisited;
	} stats;

	bool	wantToExit;
} Player;

Player* player_create(unsigned life, unsigned shield, float fuel, unsigned weight, unsigned food, unsigned power);
void	player_destroy(Player *player);

Staff	player_setByUser(void);

void	player_setLife(Player *player, unsigned life, unsigned maxLife);
void	player_setshield(Player *player, unsigned shield, unsigned maxshield);
void	player_setFuel(Player *player, float fuel, float maxFuel);
void	player_setWeight(Player *player, unsigned weight, unsigned maxWeight);
void	player_setFood(Player *player, unsigned food, unsigned maxFood);

void	player_drop(Player *player, Planet *planet);

bool	player_isDead(Player *player);
float	player_getDistanceOfPlanet(Player player, Planet planet);

void	player_info(Player player);

void	player_set_planet(Player *player);
void	player_move_toPlanet(Player *player, int dir);
void	player_move_toSystem(Player *player, StarSystem *starsystem);
void	player_move_toSatellite(Player *player);

void	player_setItem(Player *player, ItemType iType, void *item);

#endif // __PLAYER_H__