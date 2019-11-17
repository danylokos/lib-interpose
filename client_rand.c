// client_rand

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	int n = 5;
	printf("[+] Generating %i random numbers between 0 and 100:\n", n);
	srand(time(NULL));
	for (int i=0; i<n; i++) {
		printf("[%i] random numer: %i\n", i+1, rand() % 100);
	}
	return 0;
}
