#ifndef __COMMAND_H_GUARD__
#define __COMMAND_H_GUARD__

#include <stdlib.h>

#include "player.h"

#define NFUNCTIONS	7
#define MAX_LENGHT	64

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

#endif /* __COMMAND_H_GUARD__ */