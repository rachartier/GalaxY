#include "ship_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

Weapon	weapon_create_rand(unsigned level) {
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

	static float table_castTime[] = {
		1.0f,
		0.1f,
		3.0f,
		2.0f
	};

	Weapon		w;
	WeaponType	wt = rand_born(0, W_LAST - 1);

	int			mark = rand_born(0, MAXMARK(level));

	float	offset = table_weapon[mark];
	float	critic = rand_float(5.f, 21.f);

	w.damage = table_damage[wt] * offset + rand_born(0, 4 + (offset / 1.5));
	w.penArmor = table_penArmor[wt] * offset;
	w.criticalChance = critic + (9 * offset);

	w.castTime = table_castTime[wt];

	w.isVisible = true;
	w.type = wt;

	strcpy(w.name, "[Nom Arme] ");
	strcat(w.name, gTable_markName[mark]);

	return w;
}
Armor 	armor_create_rand(unsigned level) {
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
	ArmorType	at = rand_born(0, A_LAST);

	int			mark = rand_born(0, MAXMARK(level));

	a.armor = table_armor[mark];
	a.life = table_armor_life[mark];

	a.isVisible = true;
	a.type = at;

	return a;
}

Engine	engine_create_rand(unsigned level) {
	Engine	e;

	e.evasionChance = 0;
	e.isVisible = false;
	e.price = 0;
	e.speed = 0;
	e.type;

	return e;
}
Hull	hull_create_rand(unsigned level) {
	Hull	h;

	h.armor.actual = 0;
	h.isVisible = false;
	h.life.actual = 0;
	h.nMaxStaff = 0;
	h.nWeaponsSlot = 0;
	h.price = 0;
	h.type = 0;

	return h;
}

void	weapon_display(Weapon weapon) {
	static char *table_weapon_type[] = {
		"Laser",
		"Machine gun",
		"Plasma",
		"Missile"
	};

	printf("\n%s:\n", weapon.name);
	printf("\t- Type de degats: %s\n", table_weapon_type[weapon.type]);
	printf("\t- Degats: %d\n", weapon.damage);
	printf("\t- Penetration d'armure: %.3f%%\n", weapon.penArmor);
	printf("\t- Temps de chargement: %.3fs\n", weapon.castTime);
	printf("\t- Chance de coup critique: %.3f%%\n", weapon.criticalChance);
}

void	armor_display(Armor armor) {
	static char *table_armor_type[] = {
		"les lasers",
		"les machine-guns",
		"le plasma",
		"les missiles"
	};
	printf("\nArmure efficace contre %s:\n", table_armor_type[armor.type]);
	printf("\tPoint de vie: %.3f\n", armor.life);
	printf("\tPoint d'armure: %.3f\n", armor.armor);
}