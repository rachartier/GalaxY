#ifndef __COMMAND_H_GUARD__
#define __COMMAND_H_GUARD__

#include <stdlib.h>

#include "player.h"

#define NFUNCTIONS	9
#define MAX_LENGHT	64

enum {
	CMD_INFO,
	CMD_LIST,
	CMD_JUMP,
	CMD_SEARCH,
	CMD_PORTAL,
	CMD_HELP,
	CMD_RECRUITEMENT,
	CMD_FIRED,
	CMD_QUIT
};

struct s_token {
	char	str[MAX_LENGHT];
};

typedef struct s_token Token;

void		cmd_get(Player *player);

int	 parse(char *str, Token *token); // retourne l'ID de la commande

void f_cmd_info(Player *player, Token *token);
void f_cmd_list(Player *player, Token *token);
void f_cmd_jump(Player *player, Token *token);
void f_cmd_quit(Player *player, Token *token);
void f_cmd_search(Player *player, Token *token);
void f_cmd_portal(Player *player, Token *token);
void f_cmd_help(Player *player, Token *token);
void f_cmd_recruitement(Player *player, Token *token);
void f_cmd_fired(Player *player, Token *token);

#endif /* __COMMAND_H_GUARD__ */