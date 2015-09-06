#ifndef __PLAYER_H_GUARD__
#define __PLAYER_H_GUARD__

#include "planet.h"
#include "starsystem.h"
#include "crew.h"

#include <stdbool.h>
#include <string.h>

struct s_option_u {
	unsigned max;
	unsigned actual;
};

struct s_option_i {
	int max;
	int actual;
};

struct s_option_f {
	float max;
	float actual;
};

struct s_player {
	Planet		actPlanet;
	StarSystem	*actStarsystem;

	Crew		crew;

	struct s_option_f fuel;
	struct s_option_i life;
	struct s_option_u shield;
	struct s_option_u weight;
	struct s_option_u food;

	unsigned money;
	unsigned power;
	unsigned seed;

	int		planetIndex;
	int		satelliteIndex;

	struct {
		int planetsVisited;
	} stats;

	bool	wantToExit;
};

typedef struct s_player Player;

typedef struct s_option_f OptionFloat;
typedef struct s_option_i OptionInt;
typedef struct s_option_u OptionUnsigned;

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

void	player_move_toPlanet(Player *player, int dir);
void	player_move_toSystem(Player *player, StarSystem *starsystem);
void	player_move_toSatellite(Player *player);

#endif /* __PLAYER_H_GUARD__ */
