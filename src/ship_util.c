#include "ship_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rand.h"

#define NMARKS	7
#define MAXMARK(a)	((a/2 >= NMARKS) ? NMARKS - 1 : a/2)

static char *gTable_markName[] = {
	"Mark I",
	"Mark II",
	"Mark III",
	"Mark IV",
	"Mark V",
	"Mark VI",
	"Final"
};

Weapon	weapon_create_rand(unsigned level) {
	static float table_weapon[] = {
		1.f,
		1.2f,
		1.5f,
		1.8f,
		1.9f,
		2.3f,
		3.2f
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

	w.castTime = table_castTime[wt] / (offset - 0.8);

	w.isVisible = true;
	w.type = wt;

	strcpy(w.name, "Arme ");
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

	strcpy(a.name, gTable_markName[mark]);

	return a;
}

Engine	engine_create_rand(unsigned level) {
	Engine	e;

	e.evasionChance = 0;
	e.isVisible = false;
	e.price = 0;
	e.speed = 0;
	e.type = 0;

	level = 0;

	return e;
}
Hull	hull_create_rand(unsigned level) {
	Hull		h;
	HullType	ht;

	static const int table_life[] = {
		500,
		1500,
		2000,
		2500,
		4000
	};

	static const int table_max_staff[] = {
		4,
		5,
		6,
		8,
		10
	};

	static const int table_max_weapon_slot[] = {
		2,
		3,
		4,
		6,
		8
	};

	static const int table_price[] = {
		500,
		1000,
		1500,
		2000,
		5000
	};

	static const float table_fuel[] = {
		50.f,
		120.f,
		200.f,
		300.f,
		500.f
	};

	h.isVisible = true;

	if (level == 0)
		ht = H_SMALL;
	else
		ht = rand_born(0, H_LAST - 1);

	h.life.actual = table_life[ht];
	h.nMaxStaff = table_max_staff[ht];
	h.nWeaponsSlot = table_max_weapon_slot[ht];

	h.fuel.actual = h.fuel.max = table_fuel[ht];

	h.price = table_price[ht];
	h.type = ht;

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
	printf("\nArmure [%s] efficace contre %s:\n", armor.name, table_armor_type[armor.type]);
	printf("\tPoint de vie: %.3f\n", armor.life);
	printf("\tEfficacite: %.3f%%\n", armor.armor);
}

void	hull_display(Hull hull) {
	static char *hull_name[] = {
		"Tres petite",
		"Petite",
		"Normale",
		"Grande",
		"Tres grande"
	};

	printf("\nCoque (%s):", hull_name[hull.type]);
	printf("\tPoint de vie: %d/%d\n", hull.life.actual, hull.life.actual);
	printf("\tCarburant: %.3f/%.3f\n", hull.fuel.actual, hull.fuel.max);
	printf("\tPersonnel maximum: %d\n", hull.nMaxStaff);
	printf("\tNombre maximum d'armes: %d\n", hull.nWeaponsSlot);
}