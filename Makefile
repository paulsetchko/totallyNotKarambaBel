all:
	gcc -g -Wall finder.c -o finder -lcrypto

clean:
	rm -f finder
