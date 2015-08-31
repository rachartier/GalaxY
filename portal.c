#include "portal.h"

#include <string.h>

Planet createPortal(void) {
	static char a = 0;

	Planet p = {
		.radius = 20,
		.isHabitable = false,
		.isPortal = true,
		0
	};

	if (a == 0) {
		p.type = P_TYPE_PORTAL_OUT;
		strcpy(p.name, "Portail (sortie)");
	}
	else {
		p.type = P_TYPE_PORTAL_IN;
		strcpy(p.name, "Portail (entree)");
	}

	++a;

	if (a == 2)
		a = 0;

	return p;
}