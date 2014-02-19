#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define P 1000000000000000
#define E 1000000000000000000

int main()
{

	//long long int x = 1073741824;
	long int x = 1152921504606846976;
	int r = 0;
	static long int const PowersOf10[] = {1, 10, 100, 1000, 100000, 1000000, 10000000, 100000000, 1000000000, P, E};
	long int result, t;

	while (x >>= 1) {
		r++;
	}

	t = (r+1) * 1233 >> 12;
	result = t - (x < PowersOf10[t]);
	result = pow(10, result);
	printf("104857600: %lld\n", result);	
	printf("rounded down %.1f\n", (double) result/E);

	return 0;
}
