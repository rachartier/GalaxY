#ifndef __STARSYSTEME_H__
#define __STARSYSTEME_H__

#include "planet.h"

#define MAX_PLANET	18

typedef struct s_starsystem {
	Planet		planet[MAX_PLANET + 2];

	char		name[18];
	unsigned	numberPlanets;
} StarSystem;

StarSystem*	starsys_create(void);
void		starsys_destroy(StarSystem *sys);

void		add_planet(StarSystem *sys, unsigned index);

#endif // __STARSYSTEME_H__