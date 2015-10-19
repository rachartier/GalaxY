#include "rand.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

int		rand_born(int min, int max) {
	if (max - min != 0)
		return (rand() % (max - min) + min);
	return 0;
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

Name	rand_name(void) {
	Name name;

	memset(name.str, 0, 32);

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

	name.str[0] = toupper(pairs[pair1]);
	name.str[1] = pairs[pair1 + 1];

	name.str[2] = pairs[pair2];
	name.str[3] = pairs[pair2 + 1];

	name.str[4] = pairs[pair3];
	name.str[5] = pairs[pair3 + 1];

	name.str[6] = pairs[pair4];
	name.str[7] = pairs[pair4 + 1];

	int i = 0;

	while (name.str[i] != '\0') {
		if (name.str[i] == '.') {
			for (int k = i; name.str[k] != '\0'; k++) {
				name.str[k] = name.str[k + 1];
			}
		}
		i++;
	}

	name.str[i] = '\0';

	return name;
}