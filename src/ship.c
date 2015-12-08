#include "ship.h"

#include "memory.h"

void	ship_create(Ship *ship, unsigned int level, size_t nCrew) {
	unsigned min = (level == 0) ? level : level - 1;

	Weapon	w = weapon_create_rand(level);
	Armor	a = armor_create_rand(level);
	Engine	e = engine_create_rand(level);
	Hull	h = hull_create_rand(level);

	ship->power = 0u;

	ship_set_item(ship, I_WEAPON, 0, &w);
	ship_set_item(ship, I_ARMOR, 0, &a);
	ship_set_item(ship, I_ENGINE, 0, &e);
	ship_set_item(ship, I_HULL, 0, &h);

	for (int i = 1; i < h.nWeaponsSlot; ++i) {
		memset(ship->weapon[i].name, '\0', 31);
	}

	for (; nCrew > 0; --nCrew) {
		crew_add_staff(&ship->crew, staff_create());
	}
}

int		ship_get_free_slots(Ship ship) {
	for (int i = 0; i < ship.hull.nWeaponsSlot; ++i) {
		if (ship.weapon[i].name[0] == '\0')
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
		ship->hull = *(Hull *)item;
		break;
	default:
		break;
	}
}

void	ship_get_damage(Ship *ship, int amountDmg) {
	ship->hull.life.actual -= amountDmg;
}