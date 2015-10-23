#ifndef __PLANET_H__
#define __PLANET_H__

#include <stdbool.h>
#include <string.h>

#include "market.h"

#define MAX_SATELLITE	10

typedef enum e_planetType {
	P_TYPE_TERRESRTIAL,
	P_TYPE_GASEOUS,
	P_TYPE_NEPTUNIAN,
	P_TYPE_GIANT,
	P_TYPE_PORTAL_IN,
	P_TYPE_PORTAL_OUT,

	P_TYPE_LAST,

	P_TYPE_STAR
} PlanetType;

typedef enum e_planetCondition {
	CONDITION_OCEAN,
	CONDITION_DESERT,
	CONDITION_HUGE_FOREST,
	CONDITION_ICE,
	CONDITION_UNKNOW,

	CONDITION_LAST
} PlanetCondition;

typedef enum e_governementType {
	G_TYPE_MONARCHY,
	G_TYPE_DICTATORSHIP,
	G_TYPE_REPUBLIC,
	G_TYPE_COMMUNISM,
	G_TYPE_ARNACHIC,
	G_TYPE_FEUDAL,

	G_TYPE_LAST
} GovernementType;

typedef enum e_speciesType {
	S_TYPE_HUMAN,
	S_TYPE_DROID,
	S_TYPE_ALIEN,
	S_TYPE_ROCK,
	S_TYPE_INTEL,
	S_TYPE_WARBROG,

	S_TYPE_LAST
} SpecieType;

typedef enum e_economyType {
	E_TYPE_RICH,
	E_TYPE_AVERAGE,
	E_TYPE_POOR
} EconomyType;

typedef struct s_satellite {
	double		surface;
	double		radius;

	unsigned	people;

	bool		isHabitable;
	bool		visited;
} Satellite;

typedef struct s_planet {
	struct {
		float	percentageWater;
		float	percentageOther;
		float	percentageLivableArea;
		float	percentageIce;
		float	percentageDesert;
	} stat;

	struct s_satellite	satellite[MAX_SATELLITE];

	struct s_market		*market;

	unsigned	nSatellite;
	unsigned	people;

	double		radius;
	double		areaTotal;
	double		livableArea;

	float		distanceOfNearestStar;
	float		distanceOfShip;

	bool		isHabitable;
	bool		isPortal;

	bool		isGiant;
	bool		isColony;

	bool		hasWater;
	bool		canCommerce;
	bool		visited;

	enum e_speciesType		specie;
	enum e_governementType	governementType;
	enum e_planetCondition	condition;
	enum e_planetType		type;
	enum e_economyType		economy;

	char name[32];
} Planet;

Planet	planet_create(int index);
void	planet_destroy(Planet *planet);

Planet	planet_createSun(void);

void	planet_set_distanceOfStar(Planet *planet, float distance);
void	planet_set_distance(Planet *last, Planet *act, float distance);

void	planet_show_stats(Planet planet);
void	planet_show_satelliteStats(Satellite s);

double	set_percentage_of_area(double value, float offset);

void chose_random_name(Planet *planet);
void chose_random_species(Planet *planet);
void chose_random_economy(Planet *planet);
void chose_random_condition(Planet *planet);
void chose_random_governementType(Planet *planet);
void chose_random_planetType(Planet *planet, int id);

void generate_world(Planet *planet);
bool gen_non_habitable_area(Planet *planet, PlanetCondition pCondition, float percentage, int chance);

void set_people(Planet *planet);
void set_radius(Planet *planet);

void create_satellite(Planet *planet);

#endif // __PLANET_H__