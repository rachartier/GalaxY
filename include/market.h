#ifndef __MARKET_H__
#define __MARKET_H__

/*
Le systeme de combat marche comme Grandia II, c'est à dire que chaque vaisseau aura un temps d'attente et un temps de cast
ce qui pourra rendre les combats plus "realistes"

chaque arme/bouclier/machine aura 7 versions
*/

#include <stdbool.h>

#include "util.h"
#include "planet.h"
#include "ship_items.h"
#include "player.h"

#define MAX_WEAPON_ITEM	4
#define MAX_ARMOR_ITEM	3
#define MAX_ENGINE_ITEM	2
#define MAX_HULL_ITEM	2

typedef struct s_market {
	Weapon	weapon[MAX_WEAPON_ITEM];
	Armor	armor[MAX_ARMOR_ITEM];
	Engine	engine[MAX_ENGINE_ITEM];
	Hull	hull[MAX_HULL_ITEM];

	unsigned	nWeapons;
	unsigned	nArmors;
	unsigned	nEngines;
	unsigned	nHulls;

	int		nFoods;
	int		nFuels;
} Market;

void	market_create(Market *market, Planet *planet);

void	market_add_item(Market *market, ItemType iType, void *item, int id);
void	market_remove_item(Market *market, ItemType iType, int id);
void*	market_get_item(Market *market, ItemType iType, int id);
float	market_get_item_price(Market *market, ItemType iType, int id);

void	market_display(Market *market);

void	market_display_weapon(Market *market);
void	market_display_armor(Market *market);
void	market_display_engine(Market *market);
void	market_display_hull(Market *market);

void	market_display_item(Market *market, Token *token);
void	market_display_help(void);

void	market_buy(Market *market, struct s_player *player, Token *token);
void	market_buy_fuel(Market *market, Player *player, unsigned amount);
void	market_buy_food(Market *market, Player *player, unsigned amount);
void	market_buy_item(Market *market, Player *player, ItemType iType, int id);

void	market_compare(Market *market, Player *player, Token *token);

#endif // __MARKET_H__