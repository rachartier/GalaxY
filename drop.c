#include "drop.h"

#include <stdio.h>

#include "staff.h"
#include "ship_util.h"
#include "rand.h"

void	drop_staff(Player *player) {
	if (CHANCE(8)) {
		Staff staff = staff_create();
		char  c;

		printf("Vous trouvez un membre du vaisseau: ");

		staff_set_life(&staff, rand_born(10, 80));

		staff_display(staff);

		printf("Voulez vous le recruter [o/n]?");
		scanf("%c", &c);

		if (c == 'o') {
			crew_add_staff(&player->crew, staff);
		}
	}
}

void	drop_scrap(Player *player) {
	if (CHANCE(3)) {
		unsigned addmoney = rand_born(5, 20);

		printf("\t- Vous prenez %u scraps\n", addmoney);

		player->money += addmoney;
	}
}

void	drop_fuel(Player *player) {
	if (CHANCE(3)) {
		if (player->hull.fuel.actual < player->hull.fuel.max) {
			float fuel = rand_float(10.f, 30.f);

			printf("\t- Vous recuperez %.1f fuel\n", fuel);

			player_setFuel(player, player->hull.fuel.actual + fuel, player->hull.fuel.max);
		}
	}
}

void	drop_weapon(Player *player) {
	if (CHANCE(10)) {
		Weapon	w = weapon_create_rand(player->lvl);
		char	c;

		printf("Vous trouvez une arme: ");
		weapon_display(w);

		printf("Voulez vous la prendre [o/n]? ");

		scanf("%c", &c);
		if (c == 'o') {
			player_setItem(player, I_WEAPON, &w);
		}
	}
}