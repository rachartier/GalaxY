#include "command.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "planet.h"

static const char *g_commandName[] = {
	"info",
	"liste",
	"aller",
	"fouiller",
	"entrer",
	"aide",
	"quitter",
	"i",
	"ls",
	"al",
	"f",
	"e",
	"?",
	"q",
};

static const char *g_commandDetail[] = {
	"(i) [nom]: Donne des informations sur une planete, un systeme, un satellite",
	"(ls): Liste toutes les planetes du systeme actuelle",
	"(al) [prochain[e], planete/systeme] / [satellite, id]: Deplace le vaisseau",
	"(f): Permet de fouiller une planete deserte",
	"(e) [portail]: Permet d'aller dans le prochain systeme stellaire",
	"(a): Ouvre l'aide",
	"(q): Quitte le jeu"
};

void(*cmdFunction[NFUNCTIONS])(Player *, Token *) = {
	f_cmd_info,
	f_cmd_list,
	f_cmd_jump,
	f_cmd_search,
	f_cmd_portal,
	f_cmd_help,
	f_cmd_quit
};

void	cmd_get(Player *player) {
	char	str[MAX_LENGHT] = { 0 };
	Token	token[16];
	int		funcID = -1;

	printf("\n\n>>> ");

	fgets(str, MAX_LENGHT, stdin);

	if (*str != '\n') {
		funcID = parse(str, token);

		if (funcID > -1 && player != NULL)
			cmdFunction[funcID](player, token);
		else
			printf("Mauvaise commande, tapez aide\n");
	}
}

int		parse(char *str, Token *token) {
	char	*pch = NULL;
	char	delimter[] = ", .-\n";
	int		i = 0;

	pch = strtok(str, delimter);

	while (pch != NULL) {
		strcpy(token[i++].str, pch);
		pch = strtok(NULL, delimter);
	}

	for (i = 0; i < (NFUNCTIONS * 2); ++i) {
		if (strcmp(g_commandName[i], token[0].str) == 0) {
			if (i < NFUNCTIONS)
				return i;
			else
				return i - NFUNCTIONS;
		}
	}
	return -1;
}

void	f_cmd_info(Player *player, Token *token) {
	if (strcmp(token[1].str, "planete") == 0 || strcmp(token[1].str, "p") == 0) {
		planet_show_stats(player->actPlanet);
	}
	else if (strcmp(token[1].str, "satellite") == 0 || strcmp(token[1].str, "sat") == 0) {
		if (player->satelliteIndex != -1) {
			printf("\nSatellite n%u\n", player->satelliteIndex);
			planet_show_satelliteStats(player->actPlanet.satellite[player->satelliteIndex]);
		}
		else
			printf("Vous n'etes pas sur un satellite, tapez \"aller satellite [numeros]\"\n\n");
	}
	else if (strcmp(token[1].str, "systeme") == 0 || strcmp(token[1].str, "sys") == 0) {
		f_cmd_list(player, token);
	}
	else if (strcmp(token[1].str, "vaisseau") == 0 || strcmp(token[1].str, "v") == 0) {
		player_info(*player);
	}
}

void	f_cmd_list(Player *player, Token *token) {
	(void)token;

	printf("Il y a %u planetes dans ce systeme:\n", player->actStarsystem->numberPlanets - 2);

	for (unsigned i = 0; i < player->actStarsystem->numberPlanets; ++i) {
		if (player->actStarsystem->planet[i].type == P_TYPE_STAR) {
			printf("- Etoile\n");
		}
		else {
			printf("- %s", player->actStarsystem->planet[i].name);
			for (int j = strlen(player->actStarsystem->planet[i].name); j < 18; ++j)
				putchar(' ');
			printf("Habitee[%c], Visitee[%c], Dst vaisseau[%.1f]/Etoile[%.1f]\n",
				(player->actStarsystem->planet[i].isHabitable) ? 'X' : ' ',
				(player->actStarsystem->planet[i].visited) ? 'X' : ' ',
				player_getDistanceOfPlanet(*player, player->actStarsystem->planet[i]),
				player->actStarsystem->planet[i].distanceOfNearestStar);
		}
	}
}

void f_cmd_jump(Player *player, Token *token) {
	if ((strcmp(token[1].str, "prochaine") == 0 || strcmp(token[1].str, "pro") == 0)
		&& (strcmp(token[2].str, "planete") == 0 || strcmp(token[2].str, "p") == 0)) {
		player_move_toPlanet(player, 1);
	}
	else if ((strcmp(token[1].str, "precedente") == 0 || strcmp(token[1].str, "pre") == 0)
		&& (strcmp(token[2].str, "planete") == 0 || strcmp(token[2].str, "p") == 0)) {
		player_move_toPlanet(player, -1);
	}

	else if (strcmp(token[1].str, "satellite") == 0 || strcmp(token[1].str, "sat") == 0) {
		if (token[2].str != NULL) {
			int i = atoi(token[2].str);

			player->satelliteIndex = i - 1;
			player_move_toSatellite(player);
		}
	}
	else if (strcmp(token[1].str, "planete") == 0 || strcmp(token[1].str, "p") == 0) {
		if (player->satelliteIndex != -1) {
			player_move_toPlanet(player, 0);
		}
		else {
			printf("Vous etes deja sur la planete\n");
		}
	}
	else {
		printf("Mauvaise commande\n");
	}
}

void	f_cmd_quit(Player *player, Token *token) {
	(void)token;

	player->wantToExit = true;
	putchar('\n');
}

void	f_cmd_search(Player *player, Token *token) {
	(void)token;

	player_drop(player, &player->actPlanet);
}

void f_cmd_portal(Player *player, Token *token) {
	if ((strcmp(token[1].str, "portail") == 0 || strcmp(token[1].str, "p")) == 0 && player->actPlanet.type == P_TYPE_PORTAL_IN) {
		starsys_destroy(player->actStarsystem);

		StarSystem	*sys = starsys_create();
		char		c;

		printf("Attention, vous ne pourrez plus revenir dans ce systeme stellaire\nVoulez-vous continuer [o/n]?");

		scanf("%c", &c);

		if (c == 'o')
			player_move_toSystem(player, sys);
	}
	else {
		printf("Vous n'etes pas sur un portail d'entree\n");
	}
}

void f_cmd_help(Player *player, Token *token) {
	(void)player;
	(void)token;

	for (int i = 0; i < NFUNCTIONS; ++i) {
		printf("%s%s\n", g_commandName[i], g_commandDetail[i]);
		printf("-------------------------------------------------------------------------------\n");
	}
}