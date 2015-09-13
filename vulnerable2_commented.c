#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_TWEETS 528

//size is 20bytes per struct
struct live_feed {
	double tweets;
	double retweets;
	int update;
};

void launch(char * cursor, int feed_count)
{
	struct live_feed buffer[MAXIMUM_TWEETS]; //buffer size is 528 * 20 == 15600
	
	if (feed_count < MAXIMUM_TWEETS) //only do memcpy when feed_count < 528
	{       
		memcpy(buffer, cursor, feed_count * sizeof(struct live_feed)); //max copy size is 527 * 20
	}
}

int main(int argc, char * argv[])
{
	int feed_count; //int
	char * cursor; //string
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s [number of tweets],[data]\n", argv[0]); //input is ##,$EGG
		exit(EXIT_FAILURE);
	}

	feed_count = strtoul(argv[1], &cursor, 10); //convert first item to unsigned long base 10

	//using -1,$EGG where egg is size 300
	//the cursor check gets 0, the strlen check gets 1
	//the sizeof & feed count are read in as unsigned long, so if you use a negative number it will say the sizeof check is true
	if ((*cursor != ',') || (strlen(cursor + 1) < sizeof(struct live_feed) * feed_count))
	{
		fprintf(stderr, "Usage: %s [number of tweets],[data]\n", argv[0]);
		exit(EXIT_FAILURE);		
	}

	cursor = cursor + 1; //now cursor points to start of [data], this should probably be our buffer
	launch(cursor, feed_count);
	return(0);
}
