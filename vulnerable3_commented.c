#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 192

//strcpyn(buffer, 192, argv[1], strlen(argv[1]))
void strcpyn(char * destination, unsigned int destination_length, char * source, unsigned int source_length)
{
	unsigned int i;
	
	for (i = 0; i <= destination_length && i <= source_length; i++)
		destination[i] = source[i];
	//i <= strlen(argv[1]) && i<=192 , we will overwrite by one byte, which is the frame pointer?
	//buff[i]
}

void copy_user_argument(char * user_argument, unsigned int argument_length)
{
	char buffer[BUFFER_SIZE]; //buffer size == 192
	strcpyn(buffer, sizeof(buffer), user_argument, argument_length);
}

void launch(char * user_argument)
{
	copy_user_argument(user_argument, strlen(user_argument));
	//copy_user_argument(argv[1], strlen(argv[1]))
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s ARGUMENT\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	launch(argv[1]);
	return(0);
}
