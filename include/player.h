#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdbool.h>
#include <string.h>

#include "starsystem.h"
#include "planet.h"
#include "util.h"
#include "ship.h"

typedef struct s_player {
	Planet		actPlanet;
	StarSystem	*actStarsystem;

	Ship	 ship;

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

    bool    isDead;
    bool	wantToExit;
} Player;

Player* player_create();
void	player_destroy(Player *player);

Staff	player_setByUser(void);

void	player_setLife(Player *player, unsigned life, unsigned maxLife);
void	player_setFood(Player *player, unsigned food, unsigned maxFood);

void	player_drop(Player *player, Planet *planet);

bool	player_isDead(Player *player);
float	player_getDistanceOfPlanet(Player player, Planet planet);

void	player_info(Player player);

void	player_set_planet(Player *player);
void	player_move_toPlanet(Player *player, int dir);
void	player_move_toSystem(Player *player, StarSystem *starsystem);
void	player_move_toSatellite(Player *player);

void	player_setItem(Player *player, ItemType iType, int id, void *item);

#endif // __PLAYER_H__
