#include "drop.h"

#include <stdio.h>

#include "staff.h"
#include "ship_items.h"
#include "rand.h"
#include "memory.h"

void	drop_staff(Player *player) {
	if (CHANCE(7)) {
		Staff staff = staff_create();
		char  c;

		printf("Vous trouvez un membre du vaisseau: ");

		staff_set_life(&staff, rand_born(10, 80));

		staff_display(staff);

		printf("Voulez vous le recruter [o/n]?");
		scanf("%c", &c);
		purge_stdin();

		if (c == 'o') {
			if (CHANCE(10)) {
				int rep = rand_born(1, 2);
				int money;

				static const char *sentence[] = {
					"C'etait un piege! La personne que vous venez de recruter est une kamikaze!\nElle explose dans le vaisseau et fait de serieux degats...",
					"La personne vous remercies, et vous donnes %d d'argent."
				};

				switch (rep) {
				case 1:
					puts(sentence[rep - 1]);
					ship_get_damage(&player->ship, rand_born(50, player->ship.hull.life.max / 2));
					break;
				case 2:
					money = rand_born(100, 1000);
					player->money += money;
					printf(sentence[rep - 1], money);
					break;
				default:
					break;
				}
			}
			crew_add_staff(&player->ship.crew, staff);
		}
	}
}

void	drop_scrap(Player *player) {
	if (CHANCE(3)) {
		unsigned addmoney = rand_born(20, 60);

		printf("\t- Vous trouvez %u$\n", addmoney);

		player->money += addmoney;
	}
}

void	drop_fuel(Player *player) {
	if (CHANCE(3)) {
		if (player->ship.hull.fuel.actual < player->ship.hull.fuel.max) {
			float fuel = rand_float(10.f, 30.f);

			printf("\t- Vous recuperez %.1fL de carburants\n", fuel);

			player_setFuel(player, player->ship.hull.fuel.actual + fuel, player->ship.hull.fuel.max);
		}
	}
}

void	drop_weapon(Player *player) {
	if (CHANCE(10)) {
		Weapon	w = weapon_create_rand(player->lvl);
		char	c;

		printf("\nVous trouvez une arme: ");
		weapon_display(w);

		printf("Voulez vous la prendre [o/n]? ");

		scanf("%c", &c);

		purge_stdin();

		if (c == 'o') {
			player_setItem(player, I_WEAPON, 0, &w);
		}
	}
}