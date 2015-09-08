#include "commerce.h"

#include "rand.h"

#define NMARKS	8

#define MAXMARK(a)	((a/2 >= NMARKS) ? NMARKS - 1 : a/2)

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

void	commerce_create(Commerce *commerce, Planet *planet, Player *p) {
	int		randNumWeapon = rand_born(0, MAX_WEAPON_ITEM - 1);
	int		randNumArmor = rand_born(0, MAX_ARMOR_ITEM - 1);
	int		randNumEngine = rand_born(0, MAX_ENGINE_ITEM - 1);
	int		randNumHull = rand_born(0, MAX_HULL_ITEM - 1);

	for (int i = 0; i < randNumArmor; ++i) {
		Weapon w = commerce_gen_weapon(p);

		commerce_add_item(commerce, I_WEAPON, &w, i);
	}
}

Weapon	commerce_gen_weapon(Player *p) {
	static float table_weapon[] = {
		1,
		1.2,
		1.5,
		1.8,
		1.9,
		2.3,
		3.2
	};

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

	Weapon		w;
	WeaponType	wt = rand_born(0, W_LAST - 1);

	int			mark = rand_born(0, MAXMARK(p->lvl));

	float	offset = table_weapon[mark];
	float	critic = rand_float(5.f, 30.f);

	w.damage = table_damage[wt] * table_weapon[mark] + rand_born(0, 4 + (table_weapon[mark] / 1.5));
	w.penArmor = table_penArmor[wt] * table_weapon[mark];
	w.criticalChance = critic + (9 * table_weapon[mark]);

	w.isVisible = true;

	strcpy(w.name, "[Nom Arme] ");
	strcat(w.name, gTable_markName[mark]);

	return w;
}
Armor 	commerce_gen_armor(Player *p) {
	static float table_armor[] = {
		10,
		15,
		25,
		40,
		50,
		60,
		70,
		90
	};

	// A revoir
	static float table_armor_life[] = {
		100,
		400,
		800,
		1000,
		1500,
		2000,
		3000,
		5000
	};

	Armor		a;
	ArmorType	at;

	int			mark = rand_born(0, MAXMARK(p->lvl));

	a.armor = table_armor[mark];
	a.life = table_armor_life[mark];

	a.isVisible = true;
}

Engine	commerce_gen_engine(Player *p) {
}
Hull	commerce_gen_hull(Player *p) {
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