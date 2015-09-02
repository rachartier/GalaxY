#ifndef __STAFF_H_GUARD__
#define __STAFF_H_GUARD__

#include "planet.h"

#define SKILL_FACTOR	1.5

enum e_staffSkill {
	SKILL_SHIELD,
	SKILL_ATTACK,
	SKILL_PILOT,
	SKILL_ENGINE,

	SKILL_LAST
};

enum e_posInShip {
	POS_SHIELD,
	POS_ATTACK,
	POS_PILOT,
	POS_ENGINE,
	POS_UKNOW,

	POS_LAST
};

struct s_staff {
	Specie		specie;

	float		efficiency;

	unsigned	experience;
	int			life;

	enum e_posInShip	position;
	enum e_staffSkill	skill;

	char	name[32];

	bool	isDead;
};

typedef struct s_staff		Staff;

typedef enum e_staffSkill	StaffSkill;
typedef enum e_posInShip	PosInShip;

Staff	staff_create(void);

void	staff_display(Staff staff);

void	staff_add_experience(Staff *staff, unsigned amount);
void	staff_remove_life(Staff *staff, int amount);

void	staff_set_position(Staff *staff, PosInShip pos);
void	staff_set_specie(Staff *staff, Specie specie);

void	staff_gen_name(Staff *staff);

#endif /* __STAFF_H_GUARD__ */