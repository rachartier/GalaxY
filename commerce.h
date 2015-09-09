#pragma once

/*
Le systeme de combat marche comme Grandia II, c'est à dire que chaque vaisseau aura un temps d'attente et un temps de cast
ce qui pourra rendre les combats plus "realistes"

chaque arme/bouclier/machine aura 8 versions
*/

#include <stdbool.h>

#include "util.h"
#include "planet.h"
#include "ship_util.h"

#define MAX_WEAPON_ITEM	5
#define MAX_ARMOR_ITEM	3
#define MAX_ENGINE_ITEM	2
#define MAX_HULL_ITEM	2

typedef struct s_trader {
	char	name[32];

	float	offsetPrice;
} Trader;

typedef struct s_commerce {
	struct s_trader		trader;

	Weapon	weapon[MAX_WEAPON_ITEM];
	Armor	armor[MAX_ARMOR_ITEM];
	Engine	engine[MAX_ENGINE_ITEM];
	Hull	hull[MAX_HULL_ITEM];
} Commerce;

void	commerce_create(Commerce *commerce, Planet *planet, unsigned level);

void	commerce_add_item(Commerce *commerce, ItemType iType, void *item, int id);
void	commerce_remove_item(Commerce *commerce, ItemType iType, int id);

void	commerce_display(Commerce *commerce);
