#include "staff.h"

#include <string.h>

#include "rand.h"
#include "screen.h"

#define W 20
#define H 7

Staff	staff_create(void) {
	Staff	newStaff;

	newStaff.life = 100;
	newStaff.experience = rand_born(0, 100);
	newStaff.skill = rand_born(0, SKILL_LAST - 1);

	newStaff.efficiency = (float)(1 + (newStaff.experience / 1000));

	newStaff.specie = S_TYPE_HUMAN;
	newStaff.position = POS_UKNOW;

	staff_gen_name(&newStaff);

	staff_add_experience(&newStaff, (int)rand_born(10, 100));

	return newStaff;
}

void	staff_display(Staff staff) {
	static const char *g_skillName[] = {
		"Bouclier",
		"Armes",
		"Pilotage",
		"Moteur"
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