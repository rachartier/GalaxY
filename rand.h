#ifndef __RAND_GUARD_H__
#define __RAND_GUARD_H__

#define CHANCE(m) ((m == 0) || (rand_born(0, m) == ((int)m/2)))

int		rand_born(int min, int max);
int		rolld100(void);
float	rand_float(float min, float max);

char	*rand_name(void);

#endif /* __RAND_GUARD_H__ */