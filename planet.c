#include "planet.h"

#define _USE_MATH_DEFINES
#include <math.h>
#undef _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "rand.h"
#include "player.h"
// densité planete tellurique: entre 4 et 4.5

#define BORN_OCEAN		rand_float(40.f, 95.f) + rand_float(0.f, 1.f)
#define BORN_FOREST		rand_float(10.f, 60.f) + rand_float(0.f, 1.f)
#define BORN_ICE		rand_float(5.f, 20.f) + rand_float(0.f, 1.f)
#define BORN_DESERT		rand_float(5.f, 40.f) + rand_float(0.f, 1.f)

Planet		planet_create(int id) {
	Planet	p = {
		/*		.areaTotal = 0.0,
				.livableArea = 0.0,
				.people = 0,
				.isColony = false,
				.visited = false,
				.nSatellite = 0*/
				{0}
	};

	createSatellite(&p);

	choseRandomName(&p);
	choseRandomPlanetType(&p, id);
	choseRandomSpecies(&p);
	choseRandomEconomy(&p);

	setRadius(&p);

	generateWorld(&p);

	if (p.isHabitable) {
		setPeople(&p);
	}

	return p;
}

Planet		planet_createSun(void) {
	Planet	p = {
		.isColony = false,
		.type = P_TYPE_STAR,
		.isGiant = false
	};

	setRadius(&p);

	return p;
}

void		planet_setDistance(Planet *last, Planet *act, float distance) {
	planet_setDistanceOfStar(act, last->distanceOfNearestStar + distance);
}

void		planet_setDistanceOfStar(Planet *planet, float distance) {
	if (planet->type == P_TYPE_STAR)
		planet->distanceOfNearestStar = 0;
	else
		planet->distanceOfNearestStar = distance;
}

void		planet_showSatelliteStats(Satellite s) {
	printf("\tHabitable: %s\n", (s.isHabitable) ? "oui" : "non");
	if (s.isHabitable) {
		printf("\tHabitants: %u\n", s.people);
	}

	printf("\tRayon: %.3lfkm\n", s.radius);
	printf("\tSurface: %.3lfkm^2\n", s.surface);
}

void		planet_showStats(Planet planet) {
	static const char *g_speciesType[S_TYPE_LAST] = {
		"Humains",
		"Robots",
		"Aliens",
		"Rocs"
	};

	static const char *g_governementName[G_TYPE_LAST] = {
		"Monarchie",
		"Dictature",
		"Republique",
		"Communisme",
		"Arnachique",
		"Feodale"
	};

	static const char *g_planetTypeName[P_TYPE_LAST + 1] = {
		"Tellurique",
		"Gazeuse",
		"Neptunienne",
		"Geante",
		"Portail d'entrer",
		"Portail de sorti",
		"Etoile"
	};

	static const char *g_economyName[3] = {
		"Riche",
		"Moyenne",
		"Pauvre"
	};

	if (planet.type == P_TYPE_STAR) {
		printf("Est une etoile\n");
		printf("Rayon: %.3fkm", planet.radius);
		printf("\nSurface totale: %lfmillions de km^2", planet.areaTotal);
	}
	else if (planet.type == P_TYPE_PORTAL_IN || planet.type == P_TYPE_PORTAL_OUT) {
		printf("Est un %s\n", g_planetTypeName[planet.type]);
		printf("Rayon: %.3fkm\n", planet.radius);
		if (planet.type == P_TYPE_PORTAL_IN)
			printf("Tapez \"entrer portail\" pour aller dans un nouveau systeme stellaire\n");
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
			printf("\nSurface habitable: %.3lf%%", planet.stat.percentageLivableArea);
			printf("\nSurface non habitable: %.3lf%%", 100 - planet.stat.percentageLivableArea);
			printf("\nRichesse de la population: %s\n", g_economyName[planet.economy]);
		}
		for (unsigned i = 0; i < planet.nSatellite; ++i) {
			printf("\nSatellite n%u\n", i + 1);
			planet_showSatelliteStats(planet.satellite[i]);
		}
	}
}

static void generateWorld(Planet *planet) {
	if (planet->type == P_TYPE_TERRESRTIAL) {
		if (genNonHabitableArea(planet, CONDITION_OCEAN, BORN_OCEAN, 7)) {
			planet->hasWater = true;
			planet->isHabitable = true;
			planet->canCommerce = true;

			genNonHabitableArea(planet, CONDITION_DESERT, BORN_DESERT, 4);
			genNonHabitableArea(planet, CONDITION_ICE, BORN_ICE, 3);
			genNonHabitableArea(planet, CONDITION_HUGE_FOREST, BORN_FOREST, 0);
		}
		else if (CHANCE(2)) {
			planet->isColony = true;
			planet->isHabitable = true;
			planet->canCommerce = true;

			genNonHabitableArea(planet, CONDITION_UNKNOW, 0, 0);
		}
		else {
			planet->isHabitable = false;
		}
	}
	else {
		planet->isHabitable = false;
	}
}

static double setPercentageOfArea(double value, float offset) {
	if (offset != 0)
		return (value - value * offset / 100);
	else
		return value;
}

static bool genNonHabitableArea(Planet *planet, PlanetCondition pCondition, float percentage, int chance) {
	(void)pCondition;

	if (CHANCE(chance)) {
		float	areaNonHabitable;
		double	areaHabitable = planet->areaTotal;

		if (planet->isColony)
			areaNonHabitable = rand_float(70.f, 95.f);
		else
			areaNonHabitable = rand_float(0.f, percentage);

		areaHabitable = setPercentageOfArea(planet->livableArea, areaNonHabitable);

		planet->livableArea = areaHabitable;
		planet->stat.percentageLivableArea = (float)planet->livableArea * 100 / planet->areaTotal;

		return true;
	}
	return false;
}

static void choseRandomName(Planet *planet) {
	static const char	*vowel = "aeiouy";
	static const char	*consonant = "bcdfghjklmnpqrstvwxz";
	size_t				lenghtVowel = strlen(vowel);
	size_t				lenghtConsonant = strlen(consonant);

	int randomLenght = rand_born(3, 8);

	for (int i = 0; i < randomLenght; ++i) {
		char letter;
		if (i & 1)
			letter = vowel[rand_born(0, lenghtVowel)];
		else
			letter = consonant[rand_born(0, lenghtConsonant)];

		if (tolower(planet->name[i - 1]) == 'q')
			letter = 'u';
		else if (tolower(planet->name[i - 1] == 'n' && planet->name[i] == 'b'))
			planet->name[i - 1] = 'm';

		if (i == 0)
			letter = (char)toupper(letter);
		planet->name[i] = letter;
	}
}

#define BORN(s, a) (s >= bornMin[a] && s <= bornMax[a])
static void choseRandomSpecies(Planet *planet) {
	int specie;

	static const int bornMin[] = {
		0,
		13,
		15,
		16
	};

	const int bornMax[] = {
		bornMin[1] - 1,
		bornMin[2] - 1,
		bornMin[3] - 1,
		bornMin[3] + 1
	};

	specie = rand_born(0, 19);

	if (BORN(specie, S_TYPE_HUMAN)) {
		specie = S_TYPE_HUMAN;
	}
	else if (BORN(specie, S_TYPE_DROID)) {
		specie = S_TYPE_DROID;
	}
	else if (BORN(specie, S_TYPE_ALIEN)) {
		specie = S_TYPE_ALIEN;
	}
	else if (BORN(specie, S_TYPE_ROCK)) {
		specie = S_TYPE_ROCK;
	}
	else
		specie = S_TYPE_HUMAN;
	planet->specie = specie;
}

static void choseRandomEconomy(Planet *planet) {
	int eco = rand_born(E_TYPE_RICH, 3);

	planet->economy = eco;
}

static void choseRandomPlanetType(Planet *planet, int id) {
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

static void	choseRandomGovernementType(Planet *planet) {
	planet->governementType = rand_born(0, G_TYPE_LAST);
}

static void	setPeople(Planet *planet) {
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

static void setRadius(Planet *planet) {
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

static void createSatellite(Planet *planet) {
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