#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define K 1000
#define M 1000000
#define G 1000000000
#define T 1000000000000
#define P 1000000000000000
#define E 1000000000000000000	

void print_usage() {
    printf("Usage: Input an integer for rounding to 1 decimal place.\nCan include flags -K to -E.\nDefault is -K.\nUse flag -h for human-readable.\n");
    exit(2);
}

/* Log base 2 of int is the position of most significant bit set 
*  From relationship: log10(x) = log2(x)/log2(10)
*  Multiply by 1/log2(10) ~ 1233 with right shift 12 */

long int Conversion(long int input)
{
    long int lg2 = 0;
    long int lg10 = 0;
    //static long int const pow10[] = {K, M, G, T, P, E};	

    while (input >>= 1) {
	lg2++;
    }
	
    lg10 = (lg2 + 1) * 1233 >> 12;
    return pow(10, lg10);
}

int main(int argc, char **argv)
{
    if (argc < 2){
	print_usage();
    }

    int option;
    long int ans;
	
    while((option = getopt(argc, argv, "k:m:g:t:p:e:h")) != -1)
    {
	switch(option)
	{
	    case 'k' :
	        ans = Conversion(atol(optarg));
		printf("%s = %.1fK\n", optarg, (double) ans/K);
		break;

	    case 'm' :	
		ans = Conversion(atol(optarg));
		printf("%s = %.1fM\n", optarg, (double) ans/M);
		break;

	    case 'g' :
		ans = Conversion(atol(optarg));
		printf("%s = %.1fG\n", optarg, (double) ans/G);
		break;

	    case 't' :
		ans = Conversion(atol(optarg));
		printf("%s = %.1fT\n", optarg, (double) ans/T);
		break;

	    case 'p' :
		ans = Conversion(atol(optarg));
		printf("%s = %.1fP\n", optarg, (double) ans/P);
		break;

 	    case 'e' :
		ans = Conversion(atol(optarg));
		printf("%s = %.1fE\n", optarg, (double) ans/E);
		break;

	    case 'h' :
		ans = Conversion(atol(optarg));
		if (ans <= K)
		    printf("%s = %.1fK\n", optarg, (double) ans/K);
		else if (ans <= M && ans > K)
		    printf("%s = %.1fM\n", optarg, (double) ans/M);
		else if (ans <= G && ans > M)
		    printf("%s = %.1fG\n", optarg, (double) ans/G);
		else if (ans <= T && ans > G)
		    printf("%s = %.1fT\n", optarg, (double) ans/T);
		else if (ans <= P && ans > T)
		    printf("%s = %.1fP\n", optarg, (double) ans/P);
		else
		    printf("%s = %.1fE\n", optarg, (double) ans/E);
		break;

	    case '?' :
		printf("Unknown option %c.\n", optopt);
		break;

	    default :
		ans = Conversion(atol(optarg));
		printf("%s = %.1fK\n", optarg, (double) ans/K);
		break;		
	}
    }

    return 0;
} 
