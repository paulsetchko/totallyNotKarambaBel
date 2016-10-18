all:
	gcc -g -Werror -Wall finder.c main.c -o finder -lcrypto

clean:
	rm -f finder
