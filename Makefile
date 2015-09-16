CC=gcc

all:
	$(CC) atk1.c -o attack1
	$(CC) atk2.c -o attack2
	$(CC) atk3.c -o attack3
	$(CC) calc.c -o calc

clean:
	rm attack1
	rm attack2
	rm attack3
	rm calc