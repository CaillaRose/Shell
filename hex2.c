#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void hexDump (void *addr, int len)
{
	int i;
	unsigned char buffer[17];
	unsigned char *pc = (unsigned char*)addr;

	for (i=0; i<len; i++) {
		if ((i % 16) == 0) {
			if (i != 0)
				printf(" %s\n", buffer);
			printf("%08x: ", i);
		}
	
		printf(" %02x", pc[i]);
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buffer[i%16] = '.';
		else
			buffer[i%16] = pc[i];
		buffer[(i%16)+1] = '\0';
	}

	while ((i%16) != 0)
	{
		printf("  ");
		i++;
	}

	printf (" %s\n", buffer);

}*/

void hexdump(unsigned char *buffer, unsigned long index, unsigned long width)
 {
  unsigned long i,spacer;
  for (i=0;i<index;i++)
	{
	printf("%02x ",buffer[i]);
	}
  for (spacer=index;spacer<width;spacer++)
	printf("	");
  printf("| ");
  for (i=0;i<index;i++)
	{
	if (buffer[i] < 32) printf(".");
	else printf("%c",buffer[i]);
	}
  printf("\n");
 }

int hexdump_file(FILE *infile,unsigned long start, unsigned long stop, unsigned long width)
  {
  char ch;
  unsigned long f_index=0;
  unsigned long bb_index=0;
  unsigned char *byte_buffer = malloc(width);
  if (byte_buffer == NULL)
	{
	printf("Could not allocate memory for byte_buffer\n");
	return -1;
	}
  while (!feof(infile))
	{
	ch = getc(infile);	
	if ((f_index >= start)&&(f_index <= stop))
	{
	 byte_buffer[bb_index] = ch;
	 bb_index++;
	}
	if (bb_index >= width)
	{
	  hexdump(byte_buffer,bb_index,width);
	  bb_index=0;
	}	
	f_index++;	
	}
  if (bb_index)
	hexdump(byte_buffer,bb_index,width);
  fclose(infile);
  free(byte_buffer);
  return 0;
}

int main(int argc, char **argv)
{
	FILE *fptr = fopen(argv[1], "r");
	if (fptr == NULL)
	{
		printf("Problem opening file!\n");
		exit(1);
	}
	/*char *data;
	fseek(fptr, 0, SEEK_END);
	long file_sz = ftell(fptr);
	rewind(fptr);
	data = malloc(file_sz * (sizeof(char)));
	fread(data, sizeof(char), file_sz, fptr);
	fclose(fptr);

	printf("%s\n", data);

	//hexDump(&data, sizeof(data));

	char my_str[] = "a char string greater than 16 chars";
    	hexDump (&my_str, sizeof (my_str));*/

	int result = hexdump_file(fptr, 0, 100, 16);
	return 0;
}
