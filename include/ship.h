#pragma once

#include <string.h>

#include "crew.h"
#include "starsystem.h"

#include "planet.h"
#include "ship_util.h"

typedef struct s_ship {
	Crew		crew;

	Weapon		weapon;
	Armor		armor;
	Engine		engine;
	Hull		hull;

	unsigned	power;
}	Ship;

void	ship_create(Ship *ship, unsigned int level, size_t nCrew);

void	ship_set_item(Ship *ship, ItemType iType, void *item);
