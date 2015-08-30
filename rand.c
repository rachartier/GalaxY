#include "rand.h"

#include <stdlib.h>

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