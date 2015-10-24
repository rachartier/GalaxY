#ifndef __SAVE_H__
#define __SAVE_H__

#include "ship.h"
#include "ship_items.h"
#include "player.h"

typedef struct s_save_param {
	unsigned	seed;

	Player		player;

	Weapon		weapon;
	Armor		armor;
	Engine		engine;
	Hull		hull;
} SaveParametre;

void	save_create_file(void);

#endif // __SAVE_H__