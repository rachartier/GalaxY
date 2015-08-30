#ifndef __STARSYSTEM_GUARD_H__
#define __STARSYSTEM_GUARD_H__

#include "planet.h"

#define MAX_PLANET	18

struct s_starsystem {
	Planet		planet[MAX_PLANET + 2];

	char		name[18];

	unsigned	numberPlanets;
};

typedef struct s_starsystem StarSystem;

StarSystem*	starsys_create(void);
void		starsys_destroy(StarSystem *sys);

static void add_planet(StarSystem *sys, int index);

#endif /* __STARSYSTEM_GUARD_H__ */
