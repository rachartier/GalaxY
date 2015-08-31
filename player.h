#ifndef __PLAYER_H_GUARD__
#define __PLAYER_H_GUARD__

#include "planet.h"
#include "starsystem.h"

#include <stdbool.h>
#include <string.h>

struct s_optioni {
	unsigned max;
	unsigned actual;
};

struct s_optionf {
	float max;
	float actual;
};

struct s_player {
	Planet		actPlanet;
	StarSystem	*actStarsystem;

	struct s_optionf fuel;
	struct s_optioni life;
	struct s_optioni shield;
	struct s_optioni weight;
	struct s_optioni food;

	size_t	 money;
	size_t	power;
	size_t	seed;

	int		planetIndex;
	int		satelliteIndex;

	struct {
		int planetsVisited;
	} stats;

	bool	wantToExit;
};

typedef struct s_player Player;

Player* player_create(unsigned life, unsigned shield, float fuel, unsigned weight, unsigned food, unsigned power);
void	player_destroy(Player *player);

void	player_setLife(Player *player, unsigned life, unsigned maxLife);
void	player_setshield(Player *player, unsigned shield, unsigned maxshield);
void	player_setFuel(Player *player, float fuel, float maxFuel);
void	player_setWeight(Player *player, unsigned weight, unsigned maxWeight);
void	player_setFood(Player *player, unsigned food, unsigned maxFood);

void	player_drop(Player *player, Planet *planet);

bool	player_isDead(Player *player);
float	player_getDistanceOfPlanet(Player player, Planet planet);

void	player_info(Player player);

void	player_moveToPlanet(Player *player, int dir);
void	player_moveToSystem(Player *player, StarSystem *starsystem);
void	player_moveToSatellite(Player *player);

#endif /* __PLAYER_H_GUARD__ */
