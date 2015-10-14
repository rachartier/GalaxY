#include "crew.h"

#include <stdlib.h>
#include <string.h>

void	crew_generate(Crew *crew, int nStaff) {
	memset(crew->freePlace, true, MAX_STAFF * sizeof(int));

	crew->nStaff = 0;

	for (int i = 0; i < nStaff; ++i)
		crew_add_staff(crew, staff_create());
}

void	crew_add_player(Crew *crew, Staff player) {
	memset(crew->freePlace, true, MAX_STAFF * sizeof(int));

	crew->nStaff = 0;

	crew_add_staff(crew, player);
}

void	crew_add_staff(Crew *crew, Staff staff) {
	int i;

	for (i = 0; crew->freePlace[i] != true; ++i)
		;

	crew->staff[i] = staff;
	crew->freePlace[i] = false;
	crew->nStaff++;
}

void	crew_remove_staff(Crew *crew, unsigned id) {
	if (id < MAX_STAFF) {
		crew->freePlace[id] = true;
		crew->nStaff--;
	}
}

void	crew_display(Crew crew) {
	for (int i = 0; i < MAX_STAFF; ++i) {
		if (!crew.freePlace[i]) {
			staff_display(crew.staff[i]);
		}
	}
}