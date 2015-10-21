#include "ship.h"

#include "memory.h"

void	ship_create(Ship *ship, unsigned int level, size_t nCrew) {
	unsigned min = (level == 0) ? level : level - 1;

	Weapon	w = weapon_create_rand(min, level);
	Armor	a = armor_create_rand(min, level);
	Hull	h = hull_create_rand(min, level);

	ship->power = 0u;

	ship_set_item(ship, I_WEAPON, &w);
	ship_set_item(ship, I_ARMOR, &a);
	ship_set_item(ship, I_HULL, &h);

	for (; nCrew > 0; --nCrew) {
		crew_add_staff(&ship->crew, staff_create());
	}
}

void	ship_set_item(Ship *ship, ItemType iType, void *item) {
	switch (iType) {
	case I_WEAPON:
	{
		Weapon	w = *(Weapon *)item;
		ship->weapon = w;
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