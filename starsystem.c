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

		for (int index = 0; index < sys->numberPlanets; ++index) {
			add_planet(sys, index);
		}
	}

	return sys;
}

void		starsys_destroy(StarSystem *sys) {
	xfree(sys);
}

static void add_planet(StarSystem *sys, int index) {
	Planet	planet;

	if (index == 0)
		planet = planet_createSun();
	else if (index == 1 || index == sys->numberPlanets - 1)
		planet = createPortal();
	else
		planet = planet_create(index);

	{
		float fuelCost = 0.f;

		fuelCost = (float)(rand_float(6.f, 17.f));

		if (index != 0)
			planet_setDistance(&sys->planet[index - 1], &planet, fuelCost);
		else
			planet_setDistance(&sys->planet[index], &planet, fuelCost);
	}

	memcpy(&sys->planet[index], &planet, sizeof(Planet));
}