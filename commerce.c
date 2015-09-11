#include "commerce.h"

#include <stdbool.h>

#include "rand.h"
#include "ship_util.h"

void	commerce_create(Commerce *commerce, Planet *planet, unsigned level) {
	int		randNumWeapon = rand_born(0, MAX_WEAPON_ITEM);
	int		randNumArmor = rand_born(0, MAX_ARMOR_ITEM);
	int		randNumEngine = rand_born(0, MAX_ENGINE_ITEM);
	int		randNumHull = rand_born(0, MAX_HULL_ITEM);

	for (int i = 0; i < MAX_WEAPON_ITEM; ++i) {
		if (i < randNumWeapon) {
			Weapon w = weapon_create_rand(level);

			commerce_add_item(commerce, I_WEAPON, &w, i);
		}
		else
			commerce->weapon[i].isVisible = false;
	}
	for (int i = 0; i < MAX_ARMOR_ITEM; ++i) {
		if (i < randNumArmor) {
			Armor a = armor_create_rand(level);

			commerce_add_item(commerce, I_ARMOR, &a, i);
		}
		else
			commerce->armor[i].isVisible = false;
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
			commerce->engine[id] = *(Engine *)item;
			break;
		case I_HULL:
			commerce->hull[id] = *(Hull *)item;
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
			commerce->engine[id].isVisible = false;
			break;
		case I_HULL:
			commerce->hull[id].isVisible = false;
			break;
		default:
			break;
		}
	}
}

void	commerce_display(Commerce *commerce) {
	for (int i = 0; i < MAX_WEAPON_ITEM; ++i) {
		if (commerce->weapon[i].isVisible) {
			weapon_display(commerce->weapon[i]);
		}
	}
	for (int i = 0; i < MAX_ARMOR_ITEM; ++i) {
		if (commerce->armor[i].isVisible) {
			armor_display(commerce->armor[i]);
		}
	}
}