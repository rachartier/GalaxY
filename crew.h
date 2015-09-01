#ifndef __CREW_H_GUARD__
#define __CREW_H_GUARD__

#include "staff.h"

#define MAX_STAFF 10

struct s_crew {
	Staff	staff[MAX_STAFF];
};

typedef struct s_crew	Crew;

void	crew_generate(Crew *crew, int nStaff);

void	crew_add_staff(Crew *crew, Staff staff);
void	crew_remove_staff(Crew *crew);

#endif /* __CREW_H_GUARD__ */