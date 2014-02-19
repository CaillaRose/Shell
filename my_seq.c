#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_usage() 
{
    printf("Usage: Input arguments as -l LAST or -f FIRST -i [INCREMENT] -l LAST.\n Program will default to 1 if FIRST or INREMENT is omitted.\n");
    exit(2);
}

void LAST(int z)
{
    int i;
    for (i=1; i<=z; i++)
    {
	printf("%d\n", i);
    }
}

void FIRST_LAST(int a, int z)
{
    int i;
    for (i=a; i<=z; i++)
    {
	printf("%d\n", i);
    }
}

void FIRST_INC_LAST(int a, int i, int z)
{
    int val;
    for (val=a; val<=z; val+=i)
    {
	printf("%d\n", val);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
	print_usage();
    }

    int option;
    int lflag=0, fflag=0, iflag=0;

    while((option = getopt(argc, argv, "f:i:l:w")) != -1)
	{
	    switch (option)
	    {
		case 'i' :
		    if (lflag || fflag)
		    {
			print_usage();
			exit(1);
		    } else {
			lflag++;
			fflag++;
			iflag++; 
		    }
		    FIRST_INC_LAST(atoi(optarg), atoi(optarg), atoi(optarg));
		    break;
			
		case 'f' :
		    if (lflag)
		    {
			print_usage();
			exit(1);
		    } else {
			lflag++;
			fflag++;
		    }
		    FIRST_LAST(atoi(optarg), atoi(optarg));
		break;

		case 'l' :
		    LAST(atoi(optarg));
		    break;
				
		case '?' :
		    printf("Unknown option %c. \n", optopt);
		    break;
				
		default :
		    print_usage();
		}
	}

    return 0;
}
