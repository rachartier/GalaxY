#ifndef __CREW_H__
#define __CREW_H__

#include "staff.h"

#define MAX_STAFF 6

typedef struct s_crew {
	Staff		staff[MAX_STAFF];

	unsigned	nStaff;

	bool		freePlace[MAX_STAFF];
} Crew;

void	crew_generate(Crew *crew, int nStaff);

void	crew_display(Crew crew);

void	crew_add_staff(Crew *crew, Staff staff);
void	crew_add_player(Crew *crew, Staff player);

void	crew_remove_staff(Crew *crew, unsigned id);

#endif // __CREW_H__