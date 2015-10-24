#ifndef __SHIP_ITEMS_H__
#define __SHIP_ITEMS_H__

#include <stdbool.h>

#include "util.h"

typedef enum e_item_type {
	I_WEAPON,
	I_ARMOR,
	I_ENGINE,
	I_HULL,
	I_FOOD,
	I_FUEL,

	I_LAST
} ItemType;

typedef enum e_weapon_type {
	W_LASER,
	W_MACHINE_GUN,
	W_PLASMA,
	W_MISSILE,

	W_LAST
} WeaponType;

typedef enum e_armor_type {
	A_AGAINST_LASER,
	A_AGAINST_MG,
	A_AGAINST_PLASMA,
	A_AGAINST_MISSILE,

	A_LAST
} ArmorType;

typedef enum e_engine_type {
	E_NUCLEAR,
	E_FISSION,
	E_QUANTIC,
	E_ANTI_MATTER,

	E_LAST
} EngineType;

typedef enum e_hull_type {
	H_VERY_SMALL,
	H_SMALL,
	H_NORMAL,
	H_BIG,
	H_HUGE,

	H_LAST
} HullType;

typedef struct s_weapon {
	WeaponType	type;

	char	name[32];

	int		damage;

	float	penArmor;
	float	criticalChance;

	float	castTime;

	float	price;

	bool	isVisible;
} Weapon;

typedef struct s_armor {
	ArmorType	type;

	char	name[32];

	float	armor;
	float	life;

	float	price;

	bool	isVisible;
} Armor;

typedef struct s_engine {
	EngineType	type;

	char	name[32];

	int		evasionChance;

	float	speed;
	float	price;

	bool	isVisible;
} Engine;

typedef struct s_hull {
	HullType	type;

	unsigned	nWeaponsSlot;
	unsigned	nMaxStaff;

	OptionInt	life;
	OptionFloat	fuel;

	float	price;

	bool	isVisible;
} Hull;

Weapon	weapon_create_rand(unsigned playerLevel);
Armor 	armor_create_rand(unsigned playerLevel);
Engine	engine_create_rand(unsigned playerLevel);
Hull	hull_create_rand(unsigned playerLevel);

void	weapon_display(Weapon weapon);
void	armor_display(Armor armor);
void	engine_display(Engine engine);
void	hull_display(Hull hull);

#endif // __SHIP_ITEMS_H__