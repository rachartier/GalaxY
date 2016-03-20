#include "crew.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	crew_generate(Crew *crew, int nStaff) {
	memset(crew->freePlace, true, MAX_STAFF * sizeof(int));

	crew->nStaff = 0;

	for (int i = 0; i < nStaff; ++i)
		crew_add_staff(crew, staff_create());
}

void	crew_add_player(Crew *crew, Staff player) {
	memset(crew->freePlace, true, MAX_STAFF * sizeof(int));

	crew->nStaff = 0;

	crew_add_staff(crew, player);
}

void	crew_add_staff(Crew *crew, Staff staff) {
	int i;

	for (i = 0; crew->freePlace[i] != true; ++i)
		;

	crew->staff[i] = staff;
	crew->freePlace[i] = false;
	crew->nStaff++;
}

void	crew_remove_staff(Crew *crew, unsigned id) {
	if (id < MAX_STAFF) {
		crew->freePlace[id] = true;
		crew->nStaff--;
	}
}

void	crew_display(Crew crew) {
	for (int i = 0; i < MAX_STAFF; ++i) {
		if (!crew.freePlace[i]) {
			staff_display(crew.staff[i]);
		}
	}
}

void    crew_need_eat(Crew *crew, unsigned *actualFood, bool *isDead) {
   static int action = 2;
   static int turn_before_dead = 5;

   static const unsigned table_eat[] = {
        1,
        0,
        1,
        3,
        2,
        4
    };
    
    unsigned food_consommed = 0u;
    
    if(action == 0) {
        for(unsigned i = 0; i < crew->nStaff; ++i) {
            food_consommed += table_eat[crew->staff[i].specie];
        }
       
        if((int)*actualFood - (int)food_consommed < 0)
                *actualFood = 0;
        else
            *actualFood -= food_consommed;
    
        if(*actualFood == 0) {
            action = 0;
            
            if(turn_before_dead == 0) {
                printf("\n\t/!\\Vous et votre equipage etes morts de faim\n");

                *isDead = true;
            }
            else {
                printf("\n\t/!\\ Vous et votre equipage allez mourir dans %d %s si vous n'achetez pas de la nourriture\n\n", 
                                                            turn_before_dead, 
                                                            (turn_before_dead==1)? "tour" : "tours");
            }
            --turn_before_dead;

        } else {
            turn_before_dead = 5;
            action = 2;
        }
    }
    else
        --action;
 }
