#include "rand.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

int		rand_born(int min, int max) {
	return (rand() % (max - min) + min);
}

int		rolld100(void) {
	int a, b;

	a = rand_born(0, 9);
	b = rand_born(0, 9);

	a += b * 10;

	return a;
}

float	rand_float(float min, float max) {
	return min + (((float)rand() / (float)(RAND_MAX / (max - min))));
}

char	*rand_name(void) {
	char name[32] = { '\0' };
	char *pch = NULL;

	char pairs[] = { // TXTELITE.c
		"..lexegezacebiso"
		"usesarmaindirea."
		"eratenberalaveti"
		"edorquanteisrion"
	};

	size_t pairsLenght = strlen(pairs);

	int	pair1 = floor(2 * (rand_float(0.f, 1.f) * (pairsLenght / 2)));
	int pair2 = floor(2 * (rand_float(0.f, 1.f) * (pairsLenght / 2)));
	int pair3 = floor(2 * (rand_float(0.f, 1.f) * (pairsLenght / 2)));
	int pair4 = floor(2 * (rand_float(0.f, 1.f) * (pairsLenght / 2)));

	name[0] = toupper(pairs[pair1]);
	name[1] = pairs[pair1 + 1];

	name[2] = pairs[pair2];
	name[3] = pairs[pair2 + 1];

	name[4] = pairs[pair3];
	name[5] = pairs[pair3 + 1];

	name[6] = pairs[pair4];
	name[7] = pairs[pair4 + 1];

	int i = 0;

	while (name[i] != '\0') {
		if (name[i] == '.') {
			for (int k = i; name[k] != '\0'; k++) {
				name[k] = name[k + 1];
			}
		}
		i++;
	}

	name[i] = '\0';

	return name;
}