// libInter

#include "dyld-interposing.h"
#include <stdlib.h>
#include <stdio.h>

// C function

extern "C" int add(int a, int b);

int _add(int a, int b) {
	printf("interposed %s: ", __func__);
	return add(a, b);
} DYLD_INTERPOSE(_add, add)

// C struct function pointer

typedef struct AStruct {
	int (*sub)(AStruct *pAStruct, int a, int b);
} AStruct;

static int (*original_sub)(AStruct *pAStruct, int a, int b);

int _sub(AStruct *pAStruct, int a, int b) {
	printf("interposed %s: ", __func__);
    return original_sub(pAStruct, a, b);
}

extern "C" AStruct * AStruct_new();

AStruct * _AStruct_new() {
	printf("interposed %s\n", __func__);
	AStruct *pAStruct = AStruct_new();
    original_sub = pAStruct->sub;
	pAStruct->sub = _sub;
	return pAStruct;
} DYLD_INTERPOSE(_AStruct_new, AStruct_new)

// C++

class BClass {
	public:
		static int multi(int a, int b);
		double div(int a, int b);
};

// C++ static method

extern "C" int (*_ZN6BClass5multiEii)(int a2, int a3);

int _multi(int a1, int a2) {
	printf("interposed %s: ", __func__);
	return BClass::multi(a1, a2);
} DYLD_INTERPOSE(_multi, _ZN6BClass5multiEii)

// C++ method

extern "C" double (*_ZN6BClass3divEii)(BClass *pBClass, int a2, int a3);

double _div(BClass *pBClass, int a2, int a3) {
	printf("interposed %s: ", __func__);
	return pBClass->div(a2, a3);
} DYLD_INTERPOSE(_div, _ZN6BClass3divEii)
