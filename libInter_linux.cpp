// libInter

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

// C function

static int (*orig_add)(int a, int b);

extern "C" int add(int a, int b) {
	printf("interposed %s: ", __func__);
	orig_add = (int (*)(int, int))dlsym(RTLD_NEXT, "add");
	return orig_add(a, b);
}

// C struct function pointer

typedef struct AStruct {
	int (*sub)(AStruct *pAStruct, int a, int b);
} AStruct;

static int (*orig_sub)(AStruct *pAStruct, int a, int b);

int _sub(AStruct *pAStruct, int a, int b) {
	printf("interposed %s: ", __func__);
    return orig_sub(pAStruct, a, b);
}

static AStruct * (*orig_AStruct_new)();

extern "C" AStruct * AStruct_new() {
	printf("interposed %s\n", __func__);
	orig_AStruct_new = (AStruct *(*)())dlsym(RTLD_NEXT, "AStruct_new");
	AStruct *pAStruct = orig_AStruct_new();
    orig_sub = pAStruct->sub;
	pAStruct->sub = _sub;
	return pAStruct;
}

// C++

class BClass {
	public:
		static int multi(int a, int b);
		double div(int a, int b);
};

// C++ static method

static int (*orig_BClass_multi)(int a, int b);

extern "C" int _ZN6BClass5multiEii(int a, int b) {
	printf("interposed %s: ", __func__);
	orig_BClass_multi = (int (*)(int, int))dlsym(RTLD_NEXT, "_ZN6BClass5multiEii");
	return orig_BClass_multi(a, b);
}

// C++ method

static double (*orig_BClass_div)(BClass *pBClass, int a, int b);

extern "C" double _ZN6BClass3divEii(BClass *pBClass, int a, int b) {
	printf("interposed %s: ", __func__);
	orig_BClass_div = (double (*)(BClass *, int, int))dlsym(RTLD_NEXT, "_ZN6BClass3divEii");
	return orig_BClass_div(pBClass, a, b);
}
