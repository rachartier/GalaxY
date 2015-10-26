#include "market.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rand.h"
#include "ship_items.h"
#include "player.h"
#include "menu.h"
#include "memory.h"

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
	if (id >= 0 && id < MAX_WEAPON_ITEM) {
		switch (iType) {
		case I_WEAPON:
			market->weapon[id].isVisible = false;
			market->nWeapons--;
			break;
		case I_ARMOR:
			market->armor[id].isVisible = false;
			market->nArmors--;
			break;
		case I_ENGINE:
			market->engine[id].isVisible = false;
			market->nEngines--;
			break;
		case I_HULL:
			market->hull[id].isVisible = false;
			market->nHulls--;
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

float	market_get_item_price(Market *market, GovernementType gt, ItemType iType, int id) {
	if (id < MAX_WEAPON_ITEM) {
		static const float	foodPrice[] = {
			1.2f,
			1.8f,
			1.1f,
			1.1f,
			2.1f,
			3.0f
		};
		static const float	fuelPrice[] = {
			1.9f,
			2.3f,
			1.6f,
			1.7f,
			3.0f
		};

		switch (iType) {
		case I_WEAPON:
			if (id < market->nWeapons && market->weapon[id].isVisible)
				return market->weapon[id].price;
			break;
		case I_ARMOR:
			if (id < market->nArmors && market->armor[id].isVisible)
				return market->armor[id].price;
			break;
		case I_ENGINE:
			if (id < market->nEngines && market->engine[id].isVisible)
				return market->engine[id].price;
			break;
		case I_HULL:
			if (id < market->nHulls && market->hull[id].isVisible)
				return market->hull[id].price;
			break;
		case I_FOOD:
			return foodPrice[gt];
			break;
		case I_FUEL:
			return fuelPrice[gt];
			break;
		default:
			break;
		}
	}
	return -1;
}

void	market_display(Market *market, GovernementType gt) {
	menu_display_header("Commerce");

	printf("\nArmes (%d)\n", market->nWeapons);
	printf("Armures (%d)\n", market->nArmors);
	printf("Moteurs (%d)\n", market->nEngines);
	printf("Coques (%d)\n", market->nHulls);

	printf("\nAutres:");

	printf("\n- Nourriture: %d (%.3f/unite)\n", market->nFoods, market_get_item_price(market, gt, I_FOOD, 0));
	printf("- Fuels: %d (%.3f/unite)\n\n", market->nFuels, market_get_item_price(market, gt, I_FUEL, 0));
}

void	market_display_weapon(Market *market) {
	for (int i = 0; i < MAX_WEAPON_ITEM; ++i) {
		if (market->weapon[i].isVisible) {
			printf("\n[%d (prix: %.3f$)] ", i + 1, market->weapon[i].price);
			weapon_display(market->weapon[i]);
		}
		else {
			if (i < market->nWeapons)
				printf("Vendu!\n");
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
		else {
			if (i < market->nArmors)
				printf("Vendu!\n");
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
		else {
			if (i < market->nEngines)
				printf("Vendu!\n");
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
		else {
			if (i < market->nHulls)
				printf("Vendu!\n");
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
		" - Acheter nourrirutre/fuel: \"acheter [nourriture,fuel] <quantite/[max]>\"\n"
		" - Comparer deux objets: \"comparer [nom] [id]\"\n"
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
					unsigned fuelAmount = 0;

					if (strcmp(token[2].str, "max") == 0)
						fuelAmount = player->ship.hull.fuel.max - player->ship.hull.fuel.actual;
					else
						fuelAmount = (unsigned)atoi(token[2].str);

					market_buy_fuel(market, player, fuelAmount);
					break;
				}
				else if (i == I_FOOD) {
					unsigned foodAmount = (unsigned)atoi(token[2].str);

					market_buy_food(market, player, foodAmount);
					break;
				}
				else {
					int id = atoi(token[2].str) - 1;
					market_buy_item(market, player, i, id);

					break;
				}
			}
		}
	}
}
void	market_buy_fuel(Market *market, Player *player, unsigned amount) {
	float fuelPrice = amount + market_get_item_price(market, player->actPlanet.governementType, I_FUEL, 0);

	if (((market->nFuels - amount) < 0)
		|| ((player->money - fuelPrice) < 0.f)
		|| ((player->ship.hull.fuel.actual + amount) > player->ship.hull.fuel.max)) {
		printf("Vous ne pouvez pas en acheter autant!\n");
	}
	else if (player->actPlanet.governementType == G_TYPE_FEUDAL) {
		printf("Vous ne pouvez pas en acheter ici\n");
	}
	else {
		market->nFuels -= amount;
		player->money -= fuelPrice;
		player->ship.hull.fuel.actual += amount;

		printf("Vous avez achete %d fuels\n", amount);
	}
}
void	market_buy_food(Market *market, Player *player, unsigned amount) {
	float price = player->money - amount * market_get_item_price(market, player->actPlanet.governementType, I_FOOD, 0);

	if ((market->nFoods - amount < 0) || (player->money - price < 0.f))
		printf("Vous ne pouvhez pas en acheter autant!\n");
	else {
		market->nFoods -= amount;
		player->money -= price;

		printf("Vous avez achete %d de nourriture\n", amount);
	}
}
void	market_buy_item(Market *market, Player *player, ItemType iType, int id) {
	int price = market_get_item_price(market, player->actPlanet.governementType, iType, id);

	if (player->money >= price && price > 0.f) {
		if (iType == I_WEAPON) {
			int freeslot = ship_get_free_slots(player->ship);

			if (freeslot == -1) {
				int slot = -1;
				printf("Quelle arme voulez-vous remplacer: ");
				for (int i = 0; i < player->ship.hull.nWeaponsSlot; ++i) {
					printf("ID %d:", i + 1);
					weapon_display(player->ship.weapon[i]);
				}
				while (slot < 0 || slot > player->ship.hull.nWeaponsSlot) {
					printf("ID? ");
					scanf("%d", &slot);
					slot--;
					purge_stdin();
				}
				player_setItem(player, iType, slot - 1, market_get_item(market, iType, id));
			}
			else {
				player_setItem(player, iType, freeslot, market_get_item(market, iType, id));
			}
		}
		else {
			player_setItem(player, iType, 0, market_get_item(market, iType, id));
		}
		player->money -= price;

		market_remove_item(market, iType, id);
		printf("Achete!\n\n");
	}
	else
		printf("L'article n'est plus disponible ou vous n'avez pas assez d'argent...\n\n");
}

void	market_compare(Market *market, Player *player, Token *token) {
	static const char	*itemName[] = {
		"arme",
		"armure",
		"moteur",
		"coque"
	};

	for (int i = 0; i < 4; ++i) {
		if (strcmp(token[1].str, itemName[i]) == 0 && token[2].str != NULL) {
			int id = atoi(token[2].str) - 1;

			switch (i) {
			case I_WEAPON:
				if (id < market->nWeapons) {
					printf("\nVous avez:");
					for (int i = 0; i < player->ship.hull.nWeaponsSlot; ++i)
						weapon_display(player->ship.weapon[i]);
					printf("Vous regardez:");
					weapon_display(market->weapon[id]);
				}
				break;
			case I_ARMOR:
				if (id < market->nArmors) {
					printf("\nVous avez:");
					armor_display(player->ship.armor);
					printf("Vous regardez:");
					armor_display(market->armor[id]);
				}
				break;
			case I_ENGINE:
				if (id < market->nEngines) {
					printf("\nVous avez:");
					engine_display(player->ship.engine);
					printf("Vous regardez:");
					engine_display(market->engine[id]);
				}
				break;
			case I_HULL:
				if (id < market->nHulls) {
					printf("\nVous avez:");
					hull_display(player->ship.hull);
					printf("Vous regardez:");
					hull_display(market->hull[id]);
				}
				break;
			default:
				break;
			}
		}
	}
}