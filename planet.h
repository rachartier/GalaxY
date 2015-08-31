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
	double	surface;
	double	radius;

	size_t	people;

	bool	isHabitable;
	bool	visited;
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

	char	name[32];
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

static double setPercentageOfArea(double value, float offset);

static void choseRandomName(Planet *planet);
static void choseRandomSpecies(Planet *planet);
static void choseRandomEconomy(Planet *planet);
static void choseRandomCondition(Planet *planet);
static void	choseRandomGovernementType(Planet *planet);
static void choseRandomPlanetType(Planet *planet, int id);

static void generateWorld(Planet *planet);
static bool genNonHabitableArea(Planet *planet, PlanetCondition pCondition, float percentage, int chance);

static void	setPeople(Planet *planet);
static void setRadius(Planet *planet);

static void createSatellite(Planet *planet);

#endif/*__PLANET_H_GUARD__*/
