#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <stdlib.h>

#include "player.h"
#include "util.h"

#define NFUNCTIONS	11
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
	CMD_QUIT,
	CMD_COMMERCE,
	CMD_GET_ITEM_SUPPLY
};

void cmd_get(Player *player);

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
void f_cmd_commerce(Player *player, Token *token);
void f_cmd_getItemSupply(Player *player, Token *token);

#endif // __COMMAND_H__