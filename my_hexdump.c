#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16
#define MAX 100

void hexDump (unsigned char *buffer, unsigned long index)
{
	int i,j;
	unsigned char offset[SIZE+1];

	for (i=0; i<index; i++) {
		if ((i%16) == 0) {
			if (i != 0)
				printf(" %s\n", offset);
			printf(" %08x ", i);
		}
		//Print the hex code for each individual character
		printf("%02x ", buffer[i]);	
	}
	//Include spacing
	for (j=index; j<SIZE; j++) 
			printf("	");
	printf("| ");
	for (i=0; i<index; i++) {
			if ((buffer[i] < 0x20) || (buffer[i] > 0x7e))
				printf(".");
			else
				printf("%c", buffer[i]);
	}
	//Pad out last line if not exactly 16 characters
	while ((i%SIZE) != 0)
	{
		printf("  ");
		i++;
	}
	printf ("\n");

}

int main(int argc, char **argv)
{
	FILE *fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		printf("Problem opening file!\n");
		exit(1);
	}
	unsigned char *data = malloc(SIZE);
	if (data == NULL) {
		printf("Could not allocate memory for buffer\n");
		exit(1);
	}

	/*fseek(fptr, 0, SEEK_END);
	long file_sz = ftell(fptr);
	rewind(fptr);
	data = malloc(file_sz * (sizeof(char)));
	fread(data, sizeof(char), file_sz, fptr);*/

	unsigned long f_index=0, index=0;
	char ch;
	while (!feof(fptr)) {
		ch = getc(fptr);
		if ((f_index >= 0) && (f_index <= MAX)) {
			data[index] = ch;
			index++;
		}
		if (index >= SIZE) {
			hexDump(data,index);
			index = 0;
		}
		f_index++;
	}
	if (index)
		hexDump(data,index);		
	fclose(fptr);
	free(data);

	return 0;
}
