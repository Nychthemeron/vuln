#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int i;
	unsigned long j;
	int k;
	unsigned long l;
	char * ptr;
	char * ptr2;
	char * ptr3;
	char * ptr4;

	i = strtoul(argv[1], &ptr, 10);
	j = strtoul(argv[1], &ptr2, 10);

	k = strtol(argv[1], &ptr3, 10);
	l = strtol(argv[1], &ptr4, 10);

	printf("INT STRTOUL i == %i\n", i);
	printf("LONG UNSIGNED STRTOUL j == %lu\n", j);
	printf("INT STRTOL k == %i\n", k);
	printf("LONG SIGNED STRTOL l == %ld\n");

	return 1;
}