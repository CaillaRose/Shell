#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HILITE "\e[31m"
#define RESET "\e[m"	//OR "\033[0m"

void print_usage() {
    printf("Program mimics grep shell utility.\nPlease input pattern to search for followed by file to search.\nSupports optional grep arguments, -v, -c or -n)\n");
    exit(2);
}

/*Search for Pattern and Return with number of line it was found on.*/
int Line_Search(char *pattern, FILE *file) {
    int line = 1;
    int found = 0;
    char temp[600];

    while (fgets(temp, 600, file) != NULL) {
	if((strstr(temp, pattern)) != NULL) {
	printf("Match found on line: %d\n",line);
	    printf("%s\n", temp);
	    found++;
	}
	line++;
    }
	
    if (found == 0) {
	printf("\nSorry, couldn't find a match.\n");
    }
	
    return 0;
}

/*Return all lines NOT matching pattern.*/
int Invert(char *pattern, FILE *file) {
    int found = 0;
    char temp[600];
	
    while (fgets(temp, 600, file) != NULL) { 
	if((strstr(temp, pattern)) == NULL) {
 	    printf("%s\n", temp);
	    found++;
	}
    }

    if (found == 0) {
	printf("\nSorry, no NON matches found.\n");
    }

    return 0;
}

/*Return Matching Pattern highlighted in Red.*/
int Color(char *pattern, FILE *file) {
    int found = 0;
    char temp[600];

    while (fgets(temp, 600, file) != NULL) {
	if((strstr(temp, pattern)) != NULL) {
	    printf(HILITE "%s\n" RESET, temp);
	    printf(RESET);
	    found++;
	}
    }

    if (found == 0) {
	printf("\nSorry, couldn't find a match.\n");
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3){
	print_usage();
    }

    char *pattern = argv[2];
    printf("Searching for: %s\n", pattern);
	
    FILE *file = fopen(argv[3], "r");
	if (file == NULL) {
	    printf("Problem opening file!\n");
	}

    int option;

    while((option = getopt(argc, argv, "v:c:n")) != -1)
    {
	switch (option)
	{
	    case 'v' :
		Invert(pattern, file);
		break;
		
	    case 'c' :
		Color(pattern, file);
		break;
		
	    case 'n' :
		Line_Search(pattern, file);
		break;
	
	    case '?' :
		printf("Unknown option %c. \n", optopt);
		break;

	    default :
		Line_Search(pattern, file);	
		break;
		
	    }
	}

    return 0;
}
