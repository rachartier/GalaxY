#include "commerce.h"

#include "rand.h"

static char *gTable_markName[] = {
	"Mark I",
	"Mark II",
	"Mark III"
};

static float gTable_weapon[] = {
	1,
	1.6,
	2.2
};

void	commerce_create(Commerce *commerce, Planet *planet) {
	int		randNumWeapon = rand_born(0, W_LAST - 1);
	int		randNumArmor = rand_born(0, A_LAST - 1);
	int		randNumEngine = rand_born(0, E_LAST - 1);
	int		randNumHull = rand_born(0, H_LAST - 1);

	for (int i = 0; i < randNumArmor; ++i) {
		Weapon w = commerce_gen_weapon();

		commerce_add_item(commerce, I_WEAPON, &w);
	}
}

Weapon	commerce_gen_weapon(void) {
	Weapon		w;
	WeaponType	wt = rand_born(0, W_LAST - 1);
	int			mark = rand_born(0, 2);

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

	w.damage = table_damage[wt] * gTable_weapon[mark];
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

void	commerce_add_item(Commerce *commerce, ItemType iType, void *item) {
}
void	commerce_remove_item(Commerce *commerce, ItemType iType, int id) {
}
void	commerce_display(Commerce *commerce) {
}