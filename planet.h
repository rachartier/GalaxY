#ifndef __PLANET_H_GUARD__
#define __PLANET_H_GUARD__

#include <stdbool.h>
#include <string.h>

#define MAX_SATELLITE	10

enum e_planetType {
	P_TYPE_TERRESRTIAL,
	P_TYPE_GASEOUS,
	P_TYPE_NEPTUNIAN,
	P_TYPE_GIANT,
	P_TYPE_PORTAL_IN,
	P_TYPE_PORTAL_OUT,

	P_TYPE_LAST,

	P_TYPE_STAR
};

enum e_planetCondition {
	CONDITION_OCEAN,
	CONDITION_DESERT,
	CONDITION_HUGE_FOREST,
	CONDITION_ICE,
	CONDITION_UNKNOW,

	CONDITION_LAST
};

enum e_governementType {
	G_TYPE_MONARCHY,
	G_TYPE_DICTATORSHIP,
	G_TYPE_REPUBLIC,
	G_TYPE_COMMUNISM,
	G_TYPE_ARNACHIC,
	G_TYPE_FEUDAL,

	G_TYPE_LAST
};

enum e_speciesType {
	S_TYPE_HUMAN,
	S_TYPE_DROID,
	S_TYPE_ALIEN,
	S_TYPE_ROCK,

	S_TYPE_LAST
};

enum e_economyType {
	E_TYPE_RICH,
	E_TYPE_AVERAGE,
	E_TYPE_POOR
};

struct s_satellite {
	double		surface;
	double		radius;

	unsigned	people;

	bool		isHabitable;
	bool		visited;
};

struct s_planet {
	struct {
		float	percentageWater;
		float	percentageOther;
		float	percentageLivableArea;
		float	percentageIce;
		float	percentageDesert;
	} stat;

	struct	s_satellite	satellite[MAX_SATELLITE];

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
};

typedef struct s_planet		   Planet;
typedef	struct s_satellite	   Satellite;
typedef enum e_governementType GovernementType;
typedef enum e_planetCondition PlanetCondition;
typedef enum e_planetType	   PlanetType;

Planet	planet_create(int index);
Planet	planet_createSun(void);

void	planet_setDistanceOfStar(Planet *planet, float distance);
void	planet_setDistance(Planet *last, Planet *act, float distance);

void	planet_showStats(Planet planet);
void	planet_showSatelliteStats(Satellite s);

double setPercentageOfArea(double value, float offset);

void choseRandomName(Planet *planet);
void choseRandomSpecies(Planet *planet);
void choseRandomEconomy(Planet *planet);
void choseRandomCondition(Planet *planet);
void	choseRandomGovernementType(Planet *planet);
void choseRandomPlanetType(Planet *planet, int id);

void generateWorld(Planet *planet);
bool genNonHabitableArea(Planet *planet, PlanetCondition pCondition, float percentage, int chance);

void	setPeople(Planet *planet);
void setRadius(Planet *planet);
void setDensity(Planet *planet);

void createSatellite(Planet *planet);

#endif/*__PLANET_H_GUARD__*/
