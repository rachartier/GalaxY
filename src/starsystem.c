#include "starsystem.h"

#include <string.h>

#include "rand.h"
#include "portal.h"
#include "memory.h"

StarSystem*	starsys_create(void) {
	StarSystem	*sys = NULL;
	int			rndNumberOfPlanets = rand_born(9, MAX_PLANET);

	sys = xmalloc(sizeof(StarSystem));

	if (sys != NULL) {
		sys->numberPlanets = rndNumberOfPlanets;

		for (unsigned index = 0; index < sys->numberPlanets; ++index) {
			add_planet(sys, index);
		}
	}

	return sys;
}

void		starsys_destroy(StarSystem *sys) {
	for (unsigned i = 0; i < sys->numberPlanets; ++i)
		planet_destroy(&sys->planet[i]);
	xfree(sys);
}

void		add_planet(StarSystem *sys, unsigned index) {
	Planet	planet;
	float	fuelCost = 0.f;

	if (index == 0)
		planet = planet_createSun();
	else if (index == 1 || index == sys->numberPlanets - 1)
		planet = createPortal();
	else
		planet = planet_create(index);

	fuelCost = (float)(rand_float(6.f, 12.f));

	if (index != 0)
		planet_set_distance(&sys->planet[index - 1], &planet, fuelCost);
	else
		planet_set_distance(&sys->planet[index], &planet, fuelCost);

	memcpy(&sys->planet[index], &planet, sizeof(Planet));
}
