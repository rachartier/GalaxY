#pragma once

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
