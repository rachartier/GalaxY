#ifndef __UTIL_H__
#define __UTIL_H__

#define LINE(x, c) for(int i = 0; i < x; ++i) putchar(c); putchar('\n')

typedef struct s_token {
	char str[64];
} Token;

typedef struct s_option_u {
	unsigned max;
	unsigned actual;
} OptionUnsigned;

typedef struct s_option_i {
	int max;
	int actual;
} OptionInt;

typedef struct s_option_f {
	float max;
	float actual;
} OptionFloat;

#endif // __UTIL_H__
