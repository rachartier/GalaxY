#ifndef __COMMAND_H_GUARD__
#define __COMMAND_H_GUARD__

#include <stdlib.h>

#include "player.h"

#define NFUNCTIONS	7
#define MAX_LENGHT	64

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
	"a",
	"q",
};

static const char *g_commandDetail[] = {
	"(i) [nom]: Donne des informations sur une planete, un systeme, un satellite",
	"(ls): Liste toutes les planetes du systeme actuelle",
	"(al) [prochain[e], planete/systeme] / [satellite, id]: Deplace le vaisseau",
	"(f): Permet de fouiller une planete deserte",
	"(e) [portail]: Permet d'aller dans le prochain systeme stellaire",
	"(a): Ouvre l'aide",
	"(q): Quitte le jeu",
	"Raccourcis:\n"
	"\t- p: planete ou portail\n"
	"\t- sys: systeme stellaire"
	"\t- "
};

struct s_token {
	char	str[MAX_LENGHT];
};

typedef struct s_token Token;

void		cmd_get(Player *player);

static int	parse(char *str, Token *token); // retourne l'ID de la commande

static void	f_cmd_info(Player *player, Token *token);
static void	f_cmd_list(Player *player, Token *token);
static void f_cmd_jump(Player *player, Token *token);
static void	f_cmd_quit(Player *player, Token *token);
static void	f_cmd_search(Player *player, Token *token);
static void f_cmd_portail(Player *player, Token *token);
static void f_cmd_help(Player *player, Token *token);

#endif /* __COMMAND_H_GUARD__ */