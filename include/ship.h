#ifndef __SHIP_H__
#define __SHIP_H__

#include <string.h>

#include "crew.h"
#include "starsystem.h"

#include "planet.h"
#include "ship_items.h"

#define MAX_WEAPONS	8

typedef struct s_ship {
	Crew		crew;

	Weapon		weapon[8];
	Armor		armor;
	Engine		engine;
	Hull		hull;

	unsigned	power;
}	Ship;

void	ship_create(Ship *ship, unsigned int level, size_t nCrew);

int		ship_get_free_slots(Ship ship);

void	ship_set_item(Ship *ship, ItemType iType, int slot, void *item);

void	ship_get_damage(Ship *ship, int amountDmg);

#endif // __SHIP_H__