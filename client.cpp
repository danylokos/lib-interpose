// client

#include <stdio.h>
#include "libA.h"

int main(int argc, char * argv[]) {
	int a, b = 0;

	// C function
    a = 1; b = 2;
	int add_result = add(a, b);
	printf("%d+%d=%d\n", a, b, add_result);

	// C struct function pointer
    a = 3; b = 4;
	AStruct *pAStruct = AStruct_new();
	int sub_result = pAStruct->sub(pAStruct, a, b);
	AStruct_free(pAStruct);
	printf("%d-%d=%d\n", a, b, sub_result);

	// C++ static method
    a = 5; b = 6;
	int milti_result = BClass::multi(a, b);
	printf("%d*%d=%d\n", a, b, milti_result);

	// C++ method
    a = 7; b = 8;
	BClass *pBClass = new BClass();
	double div_result = pBClass->div(a, b);
	printf("%d/%d=%.2f\n", a, b, div_result);

	return 0;
}
