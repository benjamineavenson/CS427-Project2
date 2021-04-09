all: main.o keygen.o encrypt.o decrypt.o miller-rabin.o mod-exp-function.o
	gcc -o wsu-pub-crypt main.o keygen.o encrypt.o decrypt.o miller-rabin.o mod-exp-function.o -lm
main.o: main.c
	gcc -c main.c;
keygen.o: keygen.c miller-rabin.o
	gcc -c keygen.c miller-rabin.o;
encrypt.o: encrypt.c mod-exp-function.o
	gcc -c encrypt.c mod-exp-function.o;
decrypt.o: decrypt.c mod-exp-function.o
	gcc -c decrypt.c mod-exp-function.o;
miller-rabin.o: miller-rabin.c mod-exp-function.o
	gcc -c miller-rabin.c mod-exp-function.o;
mod-exp-function.o: mod-exp-function.c
	gcc -c mod-exp-function.c;
clean:
	rm *.o; rm wsu-pub-crypt;
