// libInter_rand

#include "dyld-interposing.h"

extern int rand(void);

int _rand() {
	return 42;
} DYLD_INTERPOSE(_rand, rand)
