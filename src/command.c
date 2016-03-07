#include "command.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "planet.h"
#include "rand.h"
#include "memory.h"
#include "market.h"

static const char *g_commandName[] = {
	"info",
	"liste",
	"aller",
	"fouiller",
	"entrer",
	"aide",
	"recruter",
	"virer",
	"quitter",
	"commerce",
	"recuperer",
	"i",
	"ls",
	"al",
	"f",
	"e",
	"?",
	"r",
	"v",
	"q",
	"c",
	"g"
};

static const char *g_commandDetail[] = {
	"[/vaisseau/equipage] (i [ /v/e])\n\t\t - infos sur une planete, le vaisseau, l'equipage",
	"(ls)\n\t\t - liste toutes les planetes du systeme planetaire",
	"[s/p] (al [sat/satellite][s/p])\n\t\t - permet de se deplacer",
	"(f)\n\t\t - fouiller la planete actuelle",
	"(e)\n\t\t - permet de passer au prochain systeme planetaire",
	"(?)\n\t\t - ouvre l'aide",
	"(r)\n\t\t - recrute du personnel",
	"(v)\n\t\t - vire un membre de l'equipage",
	"(q)\n\t\t - quitte le jeu",
	"(c)\n\t\t - permet d'acheter du nouveaux materiels",
	"(g)\n\t\t - recupere un objet de la cargaison"
};

void(*cmdFunction[NFUNCTIONS])(Player *, Token *) = {
	f_cmd_info,
	f_cmd_list,
	f_cmd_jump,
	f_cmd_search,
	f_cmd_portal,
	f_cmd_help,
	f_cmd_recruitement,
	f_cmd_fired,
	f_cmd_quit,
	f_cmd_commerce,
	f_cmd_getItemSupply
};

void cmd_get(Player *player) {
	char	str[MAX_LENGHT] = { 0 };
	Token	token[16];
	int		funcID = -1;

	printf("\n\n%s [%d/%d] Carburant: %.2fL>>> ", player->actPlanet.name, player->planetIndex + 1, player->actStarsystem->numberPlanets, player->ship.hull.fuel.actual);

	fgets(str, MAX_LENGHT, stdin);

	if (*str != '\n') {
		parse(str, token);

		for (int i = 0; i < (NFUNCTIONS * 2); ++i) {
			if (strcmp(g_commandName[i], token[0].str) == 0) {
				if (i < NFUNCTIONS)
					funcID = i;
				else
					funcID = i - NFUNCTIONS;
			}
		}

		if (funcID >= 0 && player != NULL)
			cmdFunction[funcID](player, token);
		else
			printf("Mauvaise commande, tapez aide ou \'?\'\n");
	}
}

int	 parse(char *str, Token *token) {
	char	*pch = NULL;
	char	delimter[] = ", .-\n";
	int		i = 0;

	pch = strtok(str, delimter);

	while (pch != NULL) {
		strcpy(token[i++].str, pch);
		pch = strtok(NULL, delimter);
	}

	return 0;
}

void f_cmd_info(Player *player, Token *token) {
	printf("%s", token[1].str);

	if (strcmp(token[1].str, "satellite") == 0 || strcmp(token[1].str, "s") == 0) {
		if (player->satelliteIndex != -1) {
			printf("\nSatellite n%u\n", player->satelliteIndex + 1);
			planet_show_satelliteStats(player->actPlanet.satellite[player->satelliteIndex]);
		}
		else
			printf("Vous n'etes pas sur un satellite, tapez \"aller satellite [numeros]\"\n\n");
	}
	else if (strcmp(token[1].str, "vaisseau") == 0 || strcmp(token[1].str, "v") == 0) {
		player_info(*player);
	}
	else if (strcmp(token[1].str, "equipage") == 0 || strcmp(token[1].str, "e") == 0) {
		crew_display(player->ship.crew);
	}
	else if ((strcmp(token[1].str, "reserve") == 0 || strcmp(token[1].str, "r") == 0)) {
		ship_list_item_supply(player->ship);
	}
	else {
		planet_show_stats(player->actPlanet);
	}
}

void f_cmd_list(Player *player, Token *token) {
	(void)token;

	printf("Il y a %u planetes dans ce systeme :\n", player->actStarsystem->numberPlanets - 1);

	for (unsigned i = 0; i < player->actStarsystem->numberPlanets; ++i) {
		if (player->actStarsystem->planet[i].type == P_TYPE_STAR) {
			printf("- Etoile\n");
		}
		else {
			int j = strlen(player->actStarsystem->planet[i].name);

			if (i == (unsigned)player->planetIndex) {
				printf("- [ %s ]", player->actStarsystem->planet[i].name);
				j += 4;
			}
			else {
				printf("- %s", player->actStarsystem->planet[i].name);
			}

			for (; j < 20; ++j)
				putchar(' ');
			printf("Hab[%c], Vis[%c], Dst. vaisseau[%.1f]/Etoile[%.1f]\n",
				(player->actStarsystem->planet[i].isHabitable) ? 'X' : ' ',
				(player->actStarsystem->planet[i].visited) ? 'X' : ' ',
				player_getDistanceOfPlanet(*player, player->actStarsystem->planet[i]),
				player->actStarsystem->planet[i].distanceOfNearestStar);
		}
	}
}

void f_cmd_jump(Player *player, Token *token) {
	if ((strcmp(token[1].str, "suiv") == 0 || strcmp(token[1].str, "s") == 0)) {
		player_move_toPlanet(player, 1);
	}
	else if ((strcmp(token[1].str, "prec") == 0 || strcmp(token[1].str, "p") == 0)) {
		player_move_toPlanet(player, -1);
	}

	// TODO : commande spéciale pour les satellites ? Ex : satellite 1 (déplace
	// sur le satellite 1 de la planète actuelle
	else if (strcmp(token[1].str, "satellite") == 0 || strcmp(token[1].str, "sat") == 0) {
		if (token[2].str != NULL) {
			int i = atoi(token[2].str);

			player->satelliteIndex = i - 1;
			player_move_toSatellite(player);
		}
	}
	else {
		printf("%s\n", g_commandDetail[CMD_JUMP]);
	}
}

void f_cmd_quit(Player *player, Token *token) {
	(void)token;

	player->wantToExit = true;
	putchar('\n');
}

void f_cmd_search(Player *player, Token *token) {
	(void)token;

	player_drop(player, &player->actPlanet);
}

void f_cmd_portal(Player *player, Token *token) {
	(void)token;

	if ((unsigned)player->planetIndex == player->actStarsystem->numberPlanets - 1) {
		char		c;

		printf("Attention, vous ne pourrez plus revenir dans ce systeme planetaire\nVoulez-vous continuer [o/n]?\n");

		scanf("%c", &c);

		if (c == 'o') {
			starsys_destroy(player->actStarsystem);
			StarSystem	*sys = starsys_create();
			player_move_toSystem(player, sys);
		}
		else {
			printf("Vous n'etes pas sur un portail d'entree\n");
		}
	}
}

void f_cmd_help(Player *player, Token *token) {
	(void)player;
	(void)token;

	putchar('\n');
	printf("COMMANDE [ARGUMENT] (VERSION COURTE [ARGUMENT]): DESCRIPTION\n\n");
	for (int i = 0; i < NFUNCTIONS; ++i) {
		LINE(80, '/');
		printf("- %s %s\n", g_commandName[i], g_commandDetail[i]);
	}
}

void f_cmd_recruitement(Player *player, Token *token) {
	(void)token;

	static const char *sentence[] = {
		"Content de vous rejoindre chef!",
		"Je ferai un formidable compagnon d'arme!",
		"Je serai fidele a vos ordres, capitaine.",
		"Ce vaisseau sera notre victoire!",
		"J'ai toujours reve d'etre a vos cote!",
		"Merci, je serai aussi serviable que possible",
		"Aux armes!",
		"C'est parti!",
		"En avant toute!"
	};

	if (CHANCE(2) && !player->actPlanet.visited && player->actPlanet.isHabitable) {
		int		n = rand_born(1, 4);
		Staff	*staff = xmalloc(n * sizeof(Staff));

		for (int i = 0; i < n; ++i) {
			staff[i] = staff_create();

			printf("ID: %d", i + 1);
			staff_display(staff[i]);
		}

		int		id = 0;

		printf("\nEntrez l'ID de la personne a recruter (entrez 0 pour annuler): ");
		scanf("%d", &id);

		if (id != 0) {
			if (player->ship.crew.nStaff < player->ship.hull.nMaxStaff) {
				while (id < 0 || id - 1 >= n) {
					printf("Mauvais ID, tapez de nouveau: ");
					scanf("%d", &id);
				}
				if (id != 0) {
					crew_add_staff(&player->ship.crew, staff[id - 1]);
					printf("%s dit: \"%s\"\n", staff[id - 1].name, sentence[rand_born(0, 8)]);
				}
			}
			else {
				printf("Nombre de personnel maximum atteint\n");
			}
		}

		xfree(staff);

		purge_stdin();
	}
	else if (!player->actPlanet.isHabitable) {
		printf("Vous ne pouvez pas recruter sur %s\n", (player->actPlanet.type == P_TYPE_PORTAL_IN || player->actPlanet.type == P_TYPE_PORTAL_OUT) ? "un portail" : "une planete deserte");
	}
	else {
		printf("Personne a recruter\n");
	}
}

void f_cmd_fired(Player *player, Token *token) {
	(void)token;

	unsigned id;

	for (unsigned i = 0; i < player->ship.crew.nStaff; ++i) {
		printf("ID: %u", i + 1);
		staff_display(player->ship.crew.staff[i]);
	}

	printf("Entrez l'ID de celui que vous voulez virer (0 pour annuler): ");
	scanf("%d", &id);

	if (id > 0 && id < player->ship.crew.nStaff + 1) {
		if (id == 1) {
			printf("Vous ne pouvez pas vous virez vous meme!\n");
		}
		else {
			printf("%s a bien ete vire\n", player->ship.crew.staff[id - 1].name);
			crew_remove_staff(&player->ship.crew, id - 1);
		}
	}
	purge_stdin();
}

void f_cmd_commerce(Player *player, Token *token) {
	(void) token;
	if (player->actPlanet.isHabitable || player->actPlanet.isColony) {
		Token	_token[16];
		char	str[128] = { '\0' };

		while (strcmp(_token[0].str, "quitter") != 0) {
			market_display(player->actPlanet.market, player->actPlanet.governementType);

			printf("[Argent: %.3f] >>> ", player->money);

			fgets(str, 128, stdin);
			parse(str, _token);

			if (strcmp(_token[0].str, "acheter") == 0) {
				market_buy(player->actPlanet.market, player, _token);
			}
			else if (strcmp(_token[0].str, "afficher") == 0) {
				market_display_item(player->actPlanet.market, _token);
			}
			else if (strcmp(_token[0].str, "comparer") == 0) {
				market_compare(player->actPlanet.market, player, _token);
			}
			else {
				market_display_help();
			}
		}
	}
	else {
		printf("Impossible de faire du commerce ici\n");
	}
}

void f_cmd_getItemSupply(Player *player, Token *token) {
	(void)token;

	unsigned id;

	ship_list_item_supply(player->ship);

	printf("\nEntrez l'ID de l'objet que vous voulez recuprer et equiper: ");
	scanf("%d", &id);

	id -= 1;

	if (id < 10) {
		if (player->ship.supply.weapon[id].isVisible && ship_get_free_slots(player->ship) != -1) {
			ship_set_item(&player->ship, I_WEAPON, ship_get_free_slots(player->ship), &player->ship.supply.weapon[id]);
			player->ship.supply.weapon[id].isVisible = false;
		}
		else if (!player->ship.supply.weapon[id].isVisible) {
			printf("Vous vous etes trompe d'ID! Veuillez re-ecrire la commande...\n");
		}
		else {
			int id2;

			printf("\nIl n'y a plus de place d'armes.\nVeuillez remplacer un emplacement d'arme (0 pour annuler)\n");

			for (unsigned i = 0; i < player->ship.hull.nWeaponsSlot; ++i) {
				printf("ID %d:", i + 1);
				weapon_display(player->ship.weapon[i]);
			}

			printf("ID: ");
			scanf("%d", &id2);

			if (id2 != 0 && id2 <= (int)player->ship.hull.nWeaponsSlot) {
				id2 -= 1;

				Weapon tmp = player->ship.weapon[id2];

				ship_set_item(&player->ship, I_WEAPON, id, &player->ship.supply.weapon[id]);
				ship_add_item_supply(&player->ship, I_WEAPON, id, &tmp);
			}
		}
		purge_stdin();
	}
	else if (id < 20) {
		if (player->ship.supply.weapon[id].isVisible)
			ship_set_item(&player->ship, I_WEAPON, ship_get_free_slots(player->ship), &player->ship.supply.weapon[id]);
	}
	else if (id < 30) {
		if (player->ship.supply.weapon[id].isVisible)
			ship_set_item(&player->ship, I_WEAPON, ship_get_free_slots(player->ship), &player->ship.supply.weapon[id]);
	}
	else {}
}
