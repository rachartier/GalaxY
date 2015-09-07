#include "commerce.h"

#include "rand.h"

#define NMARKS	5

static char *gTable_markName[] = {
	"Mark I",
	"Mark II",
	"Mark III",
	"Mark IV",
	"Mark V",
	"Mark VI",
	"Mark X",
	"Final"
};

static float gTable_weapon[] = {
	1,
	1.2,
	1.5,
	1.8,
	1.9,
	2.3,
	3.2
};

void	commerce_create(Commerce *commerce, Planet *planet) {
	int		randNumWeapon = rand_born(0, MAX_WEAPON_ITEM - 1);
	int		randNumArmor = rand_born(0, MAX_ARMOR_ITEM - 1);
	int		randNumEngine = rand_born(0, MAX_ENGINE_ITEM - 1);
	int		randNumHull = rand_born(0, MAX_HULL_ITEM - 1);

	for (int i = 0; i < randNumArmor; ++i) {
		Weapon w = commerce_gen_weapon();

		commerce_add_weapon(commerce, w, i);
	}
}

Weapon	commerce_gen_weapon(void) {
	Weapon		w;
	WeaponType	wt = rand_born(0, W_LAST - 1);

	int			mark = rand_born(0, NMARKS);

	float	offset = gTable_weapon[mark];
	float	critic = rand_float(5.f, 30.f);

	static int table_damage[] = {
		10,
		2,
		30,
		20
	};

	static float table_penArmor[] = {
		5,
		3,
		7,
		15
	};

	w.damage = table_damage[wt] * gTable_weapon[mark] + rand_born(0, 4 + (gTable_weapon[mark] / 1.5));
	w.penArmor = table_penArmor[wt] * gTable_weapon[mark];
	w.criticalChance = critic + (9 * gTable_weapon[mark]);

	strcpy(w.name, "[Nom Arme] ");
	strcat(w.name, gTable_markName[mark]);
}
Armor 	commerce_gen_armor(void) {
}
Engine	commerce_gen_engine(void) {
}
Hull	commerce_gen_hull(void) {
}

void	commerce_add_weapon(Commerce *commerce, Weapon weapon, int id) {
	if (id < MAX_WEAPON_ITEM)
		commerce->weapon[id] = weapon;
}

void	commerce_add_armor(Commerce *commerce, Armor armor, int id) {
}

void	commerce_add_engine(Commerce *commerce, Engine engine, int id) {
}

void	commerce_add_hull(Commerce *commerce, Hull hull, int id) {
}

void	commerce_remove_item(Commerce *commerce, ItemType iType, int id) {
}
void	commerce_display(Commerce *commerce) {
}