#include "commerce.h"

#include <stdbool.h>

#include "rand.h"
#include "ship_util.h"

void	commerce_create(Commerce *commerce, Planet *planet, unsigned level) {
	int		randNumWeapon = rand_born(0, MAX_WEAPON_ITEM - 1);
	int		randNumArmor = rand_born(0, MAX_ARMOR_ITEM - 1);
	int		randNumEngine = rand_born(0, MAX_ENGINE_ITEM - 1);
	int		randNumHull = rand_born(0, MAX_HULL_ITEM - 1);

	for (int i = 0; i < randNumArmor; ++i) {
		Weapon w = weapon_create_rand(level);

		commerce_add_item(commerce, I_WEAPON, &w, i);
	}
}

void	commerce_add_item(Commerce *commerce, ItemType iType, void *item, int id) {
	if (id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			commerce->weapon[id] = *(Weapon *)item;
			break;
		case I_ARMOR:
			commerce->armor[id] = *(Armor *)item;
			break;
		case I_ENGINE:

			break;
		case I_HULL:

			break;
		default:
			break;
		}
	}
}

void	commerce_remove_item(Commerce *commerce, ItemType iType, int id) {
	if (id > 0 && id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			commerce->weapon[id].isVisible = false;
			break;
		case I_ARMOR:
			commerce->armor[id].isVisible = false;
			break;
		case I_ENGINE:

			break;
		case I_HULL:

			break;
		default:
			break;
		}
	}
}

void	commerce_display(Commerce *commerce) {
}