#ifndef __COMMERCE_H_GUARD__
#define __COMMERCE_H_GUARD__

/*
Le systeme de combat marche comme Grandia II, c'est à dire que chaque vaisseau aura un temps d'attente et un temps de cast
ce qui pourra rendre les combats plus "realistes"

chaque arme/bouclier/machine aura 8 versions
*/

#include <stdbool.h>

#include "player.h"

#define MAX_WEAPON_ITEM	5
#define MAX_ARMOR_ITEM	3
#define MAX_ENGINE_ITEM	2
#define MAX_HULL_ITEM	2

typedef enum e_item_type {
	I_WEAPON,
	I_ARMOR,
	I_ENGINE,
	I_HULL,

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
	char	name[32];

	int		damage;

	float	penArmor;
	float	criticalChance;

	float	castTime;

	unsigned price;

	bool	isVisible;
} Weapon;

typedef struct s_armor {
	float	armor;
	float	life;

	unsigned price;

	bool	isVisible;
} Armor;

typedef struct s_engine {
	float	evasionChance;
	float	speed;

	unsigned price;

	bool	isVisible;
} Engine;

typedef struct s_hull {
	unsigned	nWeaponsSlot;
	unsigned	nMaxStaff;

	OptionInt		life;
	OptionUnsigned	armor;

	unsigned price;

	bool	isVisible;
} Hull;

typedef struct s_trader {
	char	name[32];

	float	offsetPrice;
} Trader;

typedef struct s_commerce {
	struct s_trader		trader;

	Weapon	weapon[MAX_WEAPON_ITEM];
	Armor	armor[MAX_ARMOR_ITEM];
	Engine	engine[MAX_ENGINE_ITEM];
	Hull	hull[MAX_HULL_ITEM];
} Commerce;

/*typedef enum e_weapon_type	WeaponType;
typedef enum e_armor_type	ArmorType;
typedef enum e_engine_type	EngineType;
typedef enum e_hull_type	HullType;

typedef enum e_item_type	ItemType;

typedef struct s_weapon		Weapon;
typedef struct s_armor		Armor;
typedef struct s_engine		Engine;
typedef struct s_hull		Hull;

typedef struct s_trader		Trader;
typedef struct s_commerce	Commerce;
*/
void	commerce_create(Commerce *commerce, Planet *planet, Player *p);

Weapon	commerce_gen_weapon(Player *p);
Armor 	commerce_gen_armor(Player *p);
Engine	commerce_gen_engine(Player *p);
Hull	commerce_gen_hull(Player *p);

void	commerce_add_item(Commerce *commerce, ItemType iType, void *item, int id);

void	commerce_remove_item(Commerce *commerce, ItemType iType, int id);

void	commerce_display(Commerce *commerce);

#endif /* __COMMERCE_H_GUARD__ */