#include "ship_items.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rand.h"
#include "ship.h"

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
		5.0,
		3.0,
		7.0,
		15.0
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

	w.damage = (int)(table_damage[wt] * offset + rand_born(0, 4 + (offset / 1.5)));
	w.penArmor = table_penArmor[wt] * offset;
	w.criticalChance = critic + (9 * offset);

	w.castTime = table_castTime[wt] / (offset);

	w.isVisible = true;
	w.type = wt;

	w.price = rand_float(1, 10) * ((mark + 1) * 1000);

	strcpy(w.name, gTable_markName[mark]);

	return w;
}
Armor 	armor_create_rand(unsigned level) {
	static float table_armor[] = {
		10.0,
		15.0,
		25.0,
		40.0,
		50.0,
		60.0,
		70.0,
		90.0f
	};

	// A revoir
	static float table_armor_life[] = {
		100.0,
		400.0,
		800.0,
		1000.0,
		1500.0,
		2000.0,
		3000.0,
		5000.0
	};

	Armor		a;
	ArmorType	at = rand_born(0, A_LAST);

	int			mark = rand_born(0, MAXMARK(level));

	a.armor = table_armor[mark];
	a.life = table_armor_life[mark];

	a.isVisible = true;
	a.type = at;

	a.price = rand_float(1, 10) * ((mark + 1) * 1000);

	strcpy(a.name, gTable_markName[mark]);

	return a;
}
Engine	engine_create_rand(unsigned level) {
	static int table_evasion[] = {
		10,
		15,
		25,
		40,
		50,
		60,
		70
	};

	Engine		e;
	EngineType	et = rand_born(0, A_LAST);

	int	mark = rand_born(0, MAXMARK(level));

	e.evasionChance = table_evasion[mark];
	e.isVisible = true;

	e.speed = 0;
	e.type = 0;

	e.price = rand_float(2, 11) * ((mark + 1) * 10000);;

	strcpy(e.name, gTable_markName[mark]);

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

	static const float table_price[] = {
		500.f,
		1000.f,
		1500.f,
		2000.f,
		5000.f
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
	h.life.max = h.life.actual;

	h.nMaxStaff = table_max_staff[ht];
	h.nWeaponsSlot = table_max_weapon_slot[ht];

	h.fuel.actual = h.fuel.max = table_fuel[ht];

	h.price = table_price[ht];
	h.type = ht;

	return h;
}

void	weapon_display(Weapon weapon) {
	if (strlen(weapon.name) > 0) {
		static char *table_weapon_type[] = {
			"Laser",
			"Machine gun",
			"Plasma",
			"Missile"
		};

		printf("\nArme [%s]:\n", weapon.name);
		printf("\t- Type de degats: %s\n", table_weapon_type[weapon.type]);
		printf("\t- Degats: %d\n", weapon.damage);
		printf("\t- Penetration d'armure: %.3f%%\n", weapon.penArmor);
		printf("\t- Temps de chargement: %.3fs\n", weapon.castTime);
		printf("\t- Chance de coup critique: %.3f%%\n", weapon.criticalChance);
	}
	else
		printf("Emplacement d'arme vide\n");
}

void	armor_display(Armor armor) {
	static char *table_armor_type[] = {
		"les lasers",
		"les machine-guns",
		"le plasma",
		"les missiles"
	};
	printf("\nArmure [%s] efficace contre %s:\n", armor.name, table_armor_type[armor.type]);
	printf("\t-Point de vie: %.3f\n", armor.life);
	printf("\t-Efficacite: %.3f%%\n", armor.armor);
}

void	engine_display(Engine engine) {
	printf("\nMoteur [%s]:\n", engine.name);
	printf("\t- Chance d'evasion: %d%%\n", engine.evasionChance);
}

void	hull_display(Hull hull) {
	static char *hull_name[] = {
		"Tres petite",
		"Petite",
		"Normale",
		"Grande",
		"Tres grande"
	};

	printf("\nCoque (%s):\n", hull_name[hull.type]);
	printf("\t-Point de vie: %d/%d\n", hull.life.actual, hull.life.max);
	printf("\t-Carburant: %.3fL/%.3fL\n", hull.fuel.actual, hull.fuel.max);
	printf("\t-Personnel maximum: %d\n", hull.nMaxStaff);
	printf("\t-Nombre maximum d'armes: %d\n", hull.nWeaponsSlot);
}