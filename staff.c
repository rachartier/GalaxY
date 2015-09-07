#include "staff.h"

#include <string.h>

#include "rand.h"
#include "screen.h"

#define W 20
#define H 7

Staff	staff_create(void) {
	Staff	newStaff;

	static const int table_life[] = {
	100,	// humain
	50,		// robot
	80,		// alien
	150,	// roc
	};

	static const float table_eff[] = {
		1.00,	// humain
		1.30,	// robot
		1.10,	// alien
		0.90	// roc
	};

	newStaff.specie = rand_born(0, S_TYPE_LAST - 1);

	newStaff.life = table_life[newStaff.specie];
	newStaff.experience = rand_born(0, 100);
	newStaff.skill = rand_born(0, SKILL_LAST - 1);

	newStaff.efficiency = (float)((table_eff[newStaff.specie]) + (newStaff.experience / 100));

	newStaff.position = POS_UKNOW;

	staff_gen_name(&newStaff);

	staff_add_experience(&newStaff, (int)rand_born(10, 100));

	return newStaff;
}

Staff	staff_create_user(char *name, Specie specie) {
	Staff	newStaff;

	static const int table_life[] = {
		200,	// humain
		100,	// robot
		160,	// alien
		300,	// roc
	};

	static const float table_eff[] = {
		2.00,	// humain
		2.60,	// robot
		2.20,	// alien
		1.81	// roc
	};

	newStaff.specie = specie;

	newStaff.life = table_life[specie];
	newStaff.experience = 0;
	newStaff.skill = SKILL_CAPTAIN;

	newStaff.efficiency = (float)((table_eff[specie]) + (newStaff.experience / 100));

	newStaff.position = POS_PILOT;

	strcpy(newStaff.name, name);

	return newStaff;
}

void	staff_display(Staff staff) {
	static const char *g_skillName[] = {
		"Bouclier",
		"Armes",
		"Pilotage",
		"Moteur",
		"Capitaine"
	};

	static const char *g_positionName[] = {
		"Bouclier",
		"Armes",
		"Pilotage",
		"Moteur",
		"Inconnue"
	};

	static const char *g_speciesType[S_TYPE_LAST] = {
		"Humain",
		"Robot",
		"Alien",
		"Roc"
	};

	printf("\n%s (%s)\n", staff.name, g_speciesType[staff.specie]);
	printf("\t- Experience: %u\n", staff.experience);
	printf("\t- Vie: %d\n", staff.life);
	printf("\t- Competence de base: %s\n", g_skillName[staff.skill]);
	printf("\t- Position dans le vaisseau: %s%s\n", (staff.position != POS_UKNOW) ? "au " : "", g_positionName[staff.position]);
	printf("\t- Efficacite: %.3f\n", staff.efficiency);
}

void	staff_add_experience(Staff *staff, unsigned amount) {
	staff->experience += amount;
}

void	staff_set_life(Staff *staff, int amount) {
	if (staff->life + amount <= 100) {
		staff->life += amount;
	}
	else
		staff->life = 100;
}

void	staff_remove_life(Staff *staff, int amount) {
	staff->life -= amount;

	if (staff->life <= 0)
		staff->isDead = true;
}

void	staff_set_position(Staff *staff, PosInShip pos) {
	if (pos < POS_LAST) {
		staff->position = pos;
		if (staff->skill == pos)
			staff->efficiency = (float)(1 + (staff->experience / 1000) + 0.2);
	}
}

void	staff_set_specie(Staff *staff, Specie specie) {
	staff->specie = specie;
}

void	staff_gen_name(Staff *staff) {
	strcpy(staff->name, rand_name());
}