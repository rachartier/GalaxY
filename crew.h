#ifndef __CREW_H_GUARD__
#define __CREW_H_GUARD__

#include "staff.h"

#define MAX_STAFF 6

struct s_crew {
	Staff		staff[MAX_STAFF];

	unsigned	nStaff;

	bool		freePlace[MAX_STAFF];
};

typedef struct s_crew	Crew;

void	crew_generate(Crew *crew, int nStaff);

void	crew_display(Crew crew);

void	crew_add_staff(Crew *crew, Staff staff);
void	crew_remove_staff(Crew *crew, int id);

#endif /* __CREW_H_GUARD__ */