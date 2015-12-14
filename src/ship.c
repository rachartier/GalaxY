#include "ship.h"

#include <stdio.h>

#include "memory.h"

void	ship_create(Ship *ship, unsigned int level, size_t nCrew) {
	unsigned min = (level == 0) ? level : level - 1;

	Weapon	w = weapon_create_rand(level);
	Armor	a = armor_create_rand(level);
	Engine	e = engine_create_rand(level);
	Hull	h = hull_create_rand(level);

	ship->power = 0u;
	ship->hull.isVisible = false;
	ship_set_item(ship, I_HULL, 0, &h);
	ship->hull.isVisible = true;

	ship_set_item(ship, I_WEAPON, 0, &w);

	ship_set_item(ship, I_ARMOR, 0, &a);
	ship_set_item(ship, I_ENGINE, 0, &e);

	for (int i = 0; i < MAX_ITEM; ++i) {
		ship->supply.weapon[i].isVisible = false;
		ship->supply.armor[i].isVisible = false;;
		ship->supply.engine[i].isVisible = false;;
	}

	ship->weapon[1].isVisible = false;
	ship->weapon[2].isVisible = false;

	for (; nCrew > 0; --nCrew) {
		crew_add_staff(&ship->crew, staff_create());
	}
}

int		ship_get_free_slots(Ship ship) {
	for (int i = 0; i < ship.hull.nWeaponsSlot; ++i) {
		if (ship.weapon[i].isVisible == false)
			return i;
	}
	return -1;
}

void	ship_set_item(Ship *ship, ItemType iType, int slot, void *item) {
	switch (iType) {
	case I_WEAPON:
	{
		Weapon	w = *(Weapon *)item;

		ship->weapon[slot] = w;
		ship->power += w.damage;
	}
	break;
	case I_ARMOR:
		ship->armor = *(Armor *)item;
		break;
	case I_ENGINE:
		ship->engine = *(Engine *)item;
		break;
	case I_HULL:
		ship_set_supply(ship);
		ship->hull = *(Hull *)item;
		break;
	default:
		break;
	}
}

void	ship_add_item_supply(Ship *ship, ItemType iType, int slot, void *item) {
	if (iType == I_WEAPON) {
		Weapon w = *(Weapon*)item;

		printf("%s a ete ajoute dans la reserve\n", w.name);
		ship->supply.weapon[slot] = w;
		//ship->supply.weapon[slot].isVisible = true;
	}
	else if (iType == I_ARMOR) {
		Armor a = *(Armor*)item;

		printf("%s a ete ajoute dans la reserve\n", a.name);
		ship->supply.armor[slot] = a;
		//ship->supply.armor[slot].isVisible = true;
	}
	else if (iType == I_ENGINE) {
		Engine e = *(Engine*)item;

		printf("%s a ete ajoute dans la reserve\n", e.name);
		ship->supply.engine[slot] = e;
		//ship->supply.engine[slot].isVisible = true;
	}
}

void	ship_set_supply(Ship *ship) {
	if (ship->hull.isVisible) {
		for (int i = 0; i < ship->hull.nWeaponsSlot; ++i) {
			if (ship->weapon[i].isVisible) {
				int j = 0;
				for (; !ship->supply.weapon[j].isVisible && j < MAX_ITEM; ++j) {}

				if (j == MAX_ITEM - 1) {
					printf("Plus de place...");
				}
				else {
					ship_add_item_supply(ship, I_WEAPON, j, &ship->weapon[i]);
					ship->weapon[i].isVisible = false;
				}
			}
		}
	}
}

void	ship_list_item_supply(Ship ship) {
	printf("\nArmes:\n");
	for (int i = 0; i < MAX_ITEM; ++i) {
		if (ship.supply.weapon[i].isVisible) {
			printf("\nID %d:", i + 1);
			weapon_display(ship.supply.weapon[i]);
		}
		else {
			printf("\tEmplacement %d vide\n", i + 1);
		}
	}

	printf("\nBoucliers:\n");
	for (int i = 0; i < MAX_ITEM; ++i) {
		if (ship.supply.armor[i].isVisible) {
			printf("\nID %d:", i + 11);
			armor_display(ship.supply.armor[i]);
		}
		else {
			printf("\tEmplacement %d vide\n", i + 11);
		}
	}

	printf("\nMoteurs:\n");
	for (int i = 0; i < MAX_ITEM; ++i) {
		if (ship.supply.engine[i].isVisible) {
			printf("\nID %d:", i + 21);
			engine_display(ship.supply.engine[i]);
		}
		else {
			printf("\tEmplacement %d vide\n", i + 21);
		}
	}
}

void	ship_get_damage(Ship *ship, int amountDmg) {
	ship->hull.life.actual -= amountDmg;
}