#include "staff.h"

#include "rand.h"

Staff	staff_create(void) {
	Staff	newStaff;

	newStaff.life = 100;
	newStaff.skill = rand_born(0, SKILL_LAST - 1);

	staff_add_experience(&newStaff, (int)rand_born(10, 100));

	return newStaff;
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
	if (pos < POS_LAST)
		staff->position = pos;
}

void	staff_set_specie(Staff *staff, Specie specie) {
	staff->specie = specie;
}

void	staff_gen_name(Staff *staff) {
	// TODO: generer des noms coherents
}