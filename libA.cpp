// libA

#include "libA.h"
#include <stdlib.h>
#include <stdio.h>

// C function

int add(int a, int b) {
	return a + b;
}

// C struct function pointer

int sub(AStruct *pAStruct, int a, int b) {
	return a - b;
}

AStruct * AStruct_new() {
	AStruct *pAStruct = (AStruct *)malloc(sizeof(AStruct));
	pAStruct->sub = &sub;
	return pAStruct;
}

void AStruct_free(AStruct *pAStruct) {
	free(pAStruct);
}

// C++

int BClass::multi(int a, int b) {
	return a * b;
}

double BClass::div(int a, int b) {
	return double(a) - double(b);
}
