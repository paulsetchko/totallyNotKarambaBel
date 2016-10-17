all:
	gcc -g -Werror -Wall finder.c -o finder -lcrypto

clean:
	rm -f finder
