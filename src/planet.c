#include "planet.h"

#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "rand.h"
#include "crew.h"
#include "player.h"
#include "memory.h"

#define M_PI			3.14159265358979323846

#define BORN_OCEAN		rand_float(40.f, 95.f) + rand_float(0.f, 1.f)
#define BORN_FOREST		rand_float(10.f, 60.f) + rand_float(0.f, 1.f)
#define BORN_ICE		rand_float(5.f, 20.f) + rand_float(0.f, 1.f)
#define BORN_DESERT		rand_float(5.f, 40.f) + rand_float(0.f, 1.f)

Planet		planet_create(int id) {
	Planet	p = {
		.areaTotal = 0.0,
		.livableArea = 0.0,
		.people = 0,
		.isColony = false,
		.visited = false,
		.nSatellite = 0
	};

	create_satellite(&p);

	chose_random_name(&p);
	chose_random_planetType(&p, id);
	chose_random_species(&p);
	chose_random_economy(&p);

	set_radius(&p);

	generate_world(&p);

	if (p.isHabitable) {
		p.market = xmalloc(sizeof(Market));
		set_people(&p);
		market_create(p.market, &p);
	}

	return p;
}
void	planet_destroy(Planet *planet) {
	if (planet->isHabitable)
		xfree(planet->market);
}

Planet		planet_createSun(void) {
	Planet	p = {
		.isColony = false,
		.type = P_TYPE_STAR,
		.isGiant = false
	};

	set_radius(&p);

	return p;
}

void		planet_set_distance(Planet *last, Planet *act, float distance) {
	planet_set_distanceOfStar(act, last->distanceOfNearestStar + distance);
}

void		planet_set_distanceOfStar(Planet *planet, float distance) {
	if (planet->type == P_TYPE_STAR)
		planet->distanceOfNearestStar = 0;
	else
		planet->distanceOfNearestStar = distance;
}

void		planet_show_satelliteStats(Satellite s) {
	printf("\tHabitable: %s\n", (s.isHabitable) ? "oui" : "non");
	if (s.isHabitable) {
		printf("\tHabitants: %u\n", s.people);
	}

	printf("\tRayon: %.3lfkm\n", s.radius);
	printf("\tSurface: %.3lfkm^2\n", s.surface);
}

void		planet_show_stats(Planet planet) {
	static const char *g_speciesType[] = {
		"Humains",
		"Robots",
		"Aliens",
		"Rocs",
		"Intel",
		"Warbrog"
	};

	static const char *g_governementName[] = {
		"Monarchie",
		"Dictature",
		"Republique",
		"Communisme",
		"Arnachique",
		"Feodale"
	};

	static const char *g_planetTypeName[] = {
		"Tellurique",
		"Gazeuse",
		"Neptunienne",
		"Geante",
		"Portail d'entrer",
		"Portail de sortie",
		"Etoile"
	};

	static const char *g_economyName[] = {
		"Riche",
		"Moyenne",
		"Pauvre"
	};

	putchar('\n');
	if (planet.type == P_TYPE_STAR) {
		printf("Est une etoile\n");
		printf("Rayon: %.3fkm", planet.radius);
		printf("\nSurface totale: %lfmillions de km^2", planet.areaTotal);
	}
	else if (planet.type == P_TYPE_PORTAL_IN || planet.type == P_TYPE_PORTAL_OUT) {
		printf("Est un %s\n", g_planetTypeName[planet.type]);
		printf("Rayon: %.3fkm\n", planet.radius);
		if (planet.type == P_TYPE_PORTAL_IN)
			printf("Tapez \"entrer\" pour aller dans un nouveau systeme planetaire\n");
	}
	else {
		printf("Nom: %s\n", planet.name);
		printf("Type: %s\n", g_planetTypeName[planet.type]);
		printf("Est une colonie: %s\n", (planet.isColony) ? "oui" : "non");
		printf("Rayon: %.3fkm", planet.radius);
		printf("\nSurface totale: %.3lf millions de km^2", planet.areaTotal);
		if (planet.isHabitable) {
			printf("\nHabitants: %u millions", planet.people);
			printf("\nEst habitee par des %s", g_speciesType[planet.specie]);
			printf("\nGouvernement en place: %s", g_governementName[planet.governementType]);
			printf("\nRichesse de la population: %s", g_economyName[planet.economy]);
			printf("\nSurface habitable: %.3lf%%", planet.stat.percentageLivableArea);
			printf("\nSurface non habitable: %.3lf%%\n", 100 - planet.stat.percentageLivableArea);
		}
		for (unsigned i = 0; i < planet.nSatellite; ++i) {
			printf("\nSatellite n%u\n", i + 1);
			planet_show_satelliteStats(planet.satellite[i]);
		}
	}
}

void generate_world(Planet *planet) {
	if (planet->type == P_TYPE_TERRESRTIAL) {
		if (gen_non_habitable_area(planet, CONDITION_OCEAN, BORN_OCEAN, 7)) {
			planet->hasWater = true;
			planet->isHabitable = true;
			planet->canCommerce = true;

			gen_non_habitable_area(planet, CONDITION_DESERT, BORN_DESERT, 4);
			gen_non_habitable_area(planet, CONDITION_ICE, BORN_ICE, 3);
			gen_non_habitable_area(planet, CONDITION_HUGE_FOREST, BORN_FOREST, 0);
		}
		else if (CHANCE(2)) {
			planet->isColony = true;
			planet->isHabitable = true;
			planet->canCommerce = true;

			gen_non_habitable_area(planet, CONDITION_UNKNOW, 0, 0);
		}
		else {
			planet->isHabitable = false;
		}
	}
	else {
		planet->isHabitable = false;
	}
}

double set_percentage_of_area(double value, float offset) {
	if (offset != 0)
		return (value - value * offset / 100);
	else
		return value;
}

bool gen_non_habitable_area(Planet *planet, PlanetCondition pCondition, float percentage, int chance) {
	(void)pCondition;

	if (CHANCE(chance)) {
		float	areaNonHabitable;
		double	areaHabitable = planet->areaTotal;

		if (planet->isColony)
			areaNonHabitable = rand_float(70.f, 90.f);
		else
			areaNonHabitable = rand_float(0.f, percentage);

		areaHabitable = set_percentage_of_area(planet->livableArea, areaNonHabitable);

		planet->livableArea = areaHabitable;
		planet->stat.percentageLivableArea = (float)(planet->livableArea * 100 / planet->areaTotal);

		return true;
	}
	return false;
}

void chose_random_name(Planet *planet) {
	static const char	*vowel = "aeiouy";
	static const char	*consonant = "bcdfghjklmnpqrstvwxz";
	size_t				lenghtVowel = strlen(vowel);
	size_t				lenghtConsonant = strlen(consonant);

	int randomLenght = rand_born(3, 8);

	for (int i = 0; i < randomLenght; ++i) {
		int letter;
		if (i & 1)
			letter = vowel[rand_born(0, lenghtVowel)];
		else
			letter = consonant[rand_born(0, lenghtConsonant)];

		if (tolower((int)planet->name[i - 1]) == 'q')
			letter = 'u';
		else if (planet->name[i - 1] == 'n' && planet->name[i] == 'b')
			planet->name[i - 1] = 'm';

		if (i == 0)
			letter = (char)toupper(letter);
		planet->name[i] = letter;
	}
}

#define BORN(s, a) (s >= bornMin[a] && s <= bornMax[a])
void chose_random_species(Planet *planet) {
	int specie;

	static const int bornMin[] = {
		0,
		8,
		12,
		14,
		16,
		20
	};

	const int bornMax[] = {
		bornMin[1] - 1,
		bornMin[2] - 1,
		bornMin[3] - 1,
		bornMin[4] - 1,
		bornMin[5] - 1,
		bornMin[5] + 6
	};

	specie = rand_born(0, bornMin[5] + 6);

	if (BORN(specie, S_TYPE_HUMAN))
		specie = S_TYPE_HUMAN;
	else if (BORN(specie, S_TYPE_DROID))
		specie = S_TYPE_DROID;
	else if (BORN(specie, S_TYPE_ALIEN))
		specie = S_TYPE_ALIEN;
	else if (BORN(specie, S_TYPE_ROCK))
		specie = S_TYPE_ROCK;
	else if (BORN(specie, S_TYPE_WARBROG))
		specie = S_TYPE_WARBROG;
	else if (BORN(specie, S_TYPE_INTEL))
		specie = S_TYPE_INTEL;
	else
		specie = S_TYPE_HUMAN;
	planet->specie = specie;
}

void chose_random_economy(Planet *planet) {
	int eco = rand_born(E_TYPE_RICH, 3);

	planet->economy = eco;
}

void chose_random_planetType(Planet *planet, int id) {
	int type;

	const int bornMin[] = {
		0,
		3,
		5
	};

	const int bornMax[] = {
		bornMin[1] - 1,
		bornMin[2] - 1,
		bornMin[2] + 1
	};

	type = rand_born(0, bornMax[2]);

	if (BORN(type, P_TYPE_TERRESRTIAL)) {
		type = P_TYPE_TERRESRTIAL;
	}
	else if (BORN(type, P_TYPE_GASEOUS) && id > 5) {
		type = P_TYPE_GASEOUS;
	}
	else if (BORN(type, P_TYPE_NEPTUNIAN) && id > 5) {
		type = P_TYPE_NEPTUNIAN;
	}
	else
		type = P_TYPE_TERRESRTIAL;

	planet->type = type;
	planet->isGiant = false;

	if (planet->type == P_TYPE_GASEOUS) {
		if (CHANCE(5)) {
			planet->isGiant = true;
		}
	}
}
#undef BORN

void	chose_random_governementType(Planet *planet) {
	planet->governementType = rand_born(0, G_TYPE_LAST);
}

void	set_people(Planet *planet) {
	double	surface = planet->livableArea; // km^2
	int		peoplePerSquareKm;

	if (!planet->isColony) {
		peoplePerSquareKm = rand_born(254, 381);
	}
	else {
		peoplePerSquareKm = rand_born((int)254 / 2, (int)381 / 2);
	}

	planet->people = (unsigned)(peoplePerSquareKm * surface) / 10;
}

void set_radius(Planet *planet) {
	double radius;

	if (planet->type == P_TYPE_STAR) {
		radius = (double)(rand_born(5, 9) + rand_float(0, 1));
		radius *= 100000;
	}
	else if (planet->isGiant && planet->type == P_TYPE_GASEOUS) {
		radius = (double)(rand_born(2, 9) + rand_float(0, 1));
		radius *= 10000;
	}
	else {
		radius = (double)(rand_born(3000, 10000) + rand_float(0, 1));
	}

	planet->radius = radius;
	planet->areaTotal = (4 * M_PI * (radius * radius)) / 1000000;
	planet->livableArea = planet->areaTotal;
}

void create_satellite(Planet *planet) {
	int nSatellite;

	if (planet->isGiant) {
		nSatellite = rand_born(2, MAX_SATELLITE);
	}
	else {
		nSatellite = rand_born(0, 3);
	}

	for (int i = 0; i < nSatellite; ++i) {
		planet->satellite[i].isHabitable = (rolld100() >= 70) ? true : false;

		planet->satellite[i].radius = (rolld100() * 10 + 700);
		planet->satellite[i].visited = false;
		planet->satellite[i].surface = (4 * M_PI * (planet->satellite[i].radius * planet->satellite[i].radius)) + rand_float(0.f, 1.f);

		if (planet->satellite[i].isHabitable) {
			planet->satellite[i].people = (unsigned)(planet->satellite[i].surface * rand_born(5, 20) / 100);
		}
	}
	planet->nSatellite = nSatellite;
}