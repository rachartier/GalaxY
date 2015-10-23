#include "Market.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rand.h"
#include "ship_items.h"
#include "player.h"

void	market_create(Market *market, Planet *planet) {
	market->nWeapons = rand_born(0, MAX_WEAPON_ITEM);
	market->nArmors = rand_born(0, MAX_ARMOR_ITEM);
	market->nEngines = rand_born(0, MAX_ENGINE_ITEM);
	market->nHulls = rand_born(0, MAX_HULL_ITEM);

	market->nFoods = (unsigned)rand_born(10, 100);
	market->nFuels = (unsigned)rand_born(50, 400);

	for (int i = 0; i < MAX_WEAPON_ITEM; ++i) {
		if (i < market->nWeapons) {
			Weapon w = weapon_create_rand(100);

			w.price *= (planet->governementType + 1) / 2.5;

			market_add_item(market, I_WEAPON, &w, i);
		}
		else
			market->weapon[i].isVisible = false;
	}
	for (int i = 0; i < MAX_ARMOR_ITEM; ++i) {
		if (i < market->nArmors) {
			Armor a = armor_create_rand(100);
			a.price *= (planet->governementType + 1) / 2.5;
			market_add_item(market, I_ARMOR, &a, i);
		}
		else
			market->armor[i].isVisible = false;
	}
	for (int i = 0; i < MAX_ENGINE_ITEM; ++i) {
		if (i < market->nEngines) {
			Engine a = engine_create_rand(100);
			a.price *= (planet->governementType + 1) / 2.5;
			market_add_item(market, I_ENGINE, &a, i);
		}
		else
			market->engine[i].isVisible = false;
	}
	for (int i = 0; i < MAX_HULL_ITEM; ++i) {
		if (i < market->nHulls) {
			Hull a = hull_create_rand(100);
			a.price *= (planet->governementType + 1) / 2.5;
			market_add_item(market, I_HULL, &a, i);
		}
		else
			market->hull[i].isVisible = false;
	}
}

void	market_add_item(Market *market, ItemType iType, void *item, int id) {
	if (id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			market->weapon[id] = *(Weapon *)item;
			break;
		case I_ARMOR:
			market->armor[id] = *(Armor *)item;
			break;
		case I_ENGINE:
			market->engine[id] = *(Engine *)item;
			break;
		case I_HULL:
			market->hull[id] = *(Hull *)item;
			break;
		default:
			break;
		}
	}
}

void	market_remove_item(Market *market, ItemType iType, int id) {
	if (id > 0 && id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			market->weapon[id].isVisible = false;
			break;
		case I_ARMOR:
			market->armor[id].isVisible = false;
			break;
		case I_ENGINE:
			market->engine[id].isVisible = false;
			break;
		case I_HULL:
			market->hull[id].isVisible = false;
			break;
		default:
			break;
		}
	}
}

void*	market_get_item(Market *market, ItemType iType, int id) {
	if (id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			if (id < market->nWeapons)
				return &market->weapon[id];
			break;
		case I_ARMOR:
			if (id < market->nArmors)
				return &market->armor[id];
			break;
		case I_ENGINE:
			if (id < market->nEngines)
				return &market->engine[id];
			break;
		case I_HULL:
			if (id < market->nHulls)
				return &market->hull[id];
			break;
		default:
			break;
		}
	}
	return NULL;
}

int		market_get_item_price(Market *market, ItemType iType, int id) {
	if (id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			if (id < market->nWeapons)
				return market->weapon[id].price;
			break;
		case I_ARMOR:
			if (id < market->nArmors)
				return market->armor[id].price;
			break;
		case I_ENGINE:
			if (id < market->nEngines)
				return market->engine[id].price;
			break;
		case I_HULL:
			if (id < market->nHulls)
				return market->hull[id].price;
			break;
		default:
			break;
		}
	}
	return -1;
}

void	market_display(Market *market) {
	int i = 0;

	if (market->nWeapons > 0)
		printf("Armes (%d)\n", market->nWeapons);
	if (market->nArmors > 0)
		printf("Armures (%d)\n", market->nArmors);
	if (market->nEngines > 0)
		printf("Moteurs (%d)\n", market->nEngines);
	if (market->nHulls > 0)
		printf("Coques (%d)\n", market->nHulls);

	printf("\n\tAUTRES:");

	printf("\n- Nourriture: %u\n", market->nFoods);
	printf("- Fuels: %u\n\n", market->nFuels);
}

void	market_display_weapon(Market *market) {
	for (int i = 0; i < MAX_WEAPON_ITEM; ++i) {
		if (market->weapon[i].isVisible) {
			printf("\n[%d (prix: %.3f$)] ", i + 1, market->weapon[i].price);
			weapon_display(market->weapon[i]);
		}
	}
}
void	market_display_armor(Market *market) {
	printf("\nARMURES:\n");
	for (int i = 0; i < MAX_ARMOR_ITEM; ++i) {
		if (market->armor[i].isVisible) {
			printf("[%d (prix: %.3f$)] ", i + 1, market->armor[i].price);
			armor_display(market->armor[i]);
		}
	}
}
void	market_display_engine(Market *market) {
	printf("\nMOTEURS:\n");
	for (int i = 0; i < MAX_ENGINE_ITEM; ++i) {
		if (market->engine[i].isVisible) {
			printf("\n[%d (prix: %.3f$)] ", i + 1, market->engine[i].price);
			engine_display(market->engine[i]);
		}
	}
}
void	market_display_hull(Market *market) {
	printf("\nCOQUES:\n");
	for (int i = 0; i < MAX_HULL_ITEM; ++i) {
		if (market->hull[i].isVisible) {
			printf("\n[%d (prix: %.3f$)] ", i + 1, market->hull[i].price);
			hull_display(market->hull[i]);
		}
	}
}
void	market_display_item(Market *market, Token *token) {
	static const char	*itemName[] = {
		"armes",
		"armures",
		"moteurs",
		"coques"
	};

	void(*displayFunction[4])(Market *market) = {
		market_display_weapon,
		market_display_armor,
		market_display_engine,
		market_display_hull
	};

	for (int i = 0; i < 4; ++i) {
		if (strcmp(token[1].str, itemName[i]) == 0) {
			displayFunction[i](market);
		}
	}
}

void	market_display_help(void) {
	const char *help = {
		"\n\nAIDE: \n"
		" - Afficher une categorie: \"afficher <nom-categorie>\"\n"
		" - Acheter un objet: \"acheter <nom-objet>[arme, armure, moteur, coque] <id>\"\n"
		" - Acheter nourrirutre/fuel: \"acheter [nourriture,fuel] <quantite>\"\n"
	};
	printf("%s\n\n", help);
}

void	market_buy(Market *market, Player *player, Token *token) {
	static const char	*itemName[] = {
		"arme",
		"armure",
		"moteur",
		"coque",
		"nourriture",
		"fuel"
	};

	if (token[1].str[0] != '\0') {
		for (int i = 0; i < 6; ++i) {
			if (strcmp(token[1].str, itemName[i]) == 0) {
				if (i == I_FUEL) {
					unsigned fuel = (unsigned)atoi(token[2].str);
					if (market->nFuels - fuel < 0)
						printf("Vous ne pouvhez pas en acheter autant!\n");
					else
						market->nFuels -= fuel;
				}
				else if (i == I_FOOD) {
					unsigned food = (unsigned)atoi(token[2].str);
					if (market->nFoods - food < 0)
						printf("Vous ne pouvhez pas en acheter autant!\n");
					else
						market->nFoods -= food;
				}
				else {
					int id = atoi(token[2].str) - 1;
					int price = market_get_item_price(market, i, id);

					if (player->money >= price) {
						player_setItem(player, i, market_get_item(market, i, id));
						player->money -= price;

						market_remove_item(market, i, id);
						printf("Achete!\n\n");
					}
					else
						printf("Pas assez d'argent...\n\n");
				}
			}
		}
	}
}