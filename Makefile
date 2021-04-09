all: main.c keygen.c encrypt.c decrypt.c miller-rabin.c mod-exp-function.c
	gcc -o wsu-pub-crypt main.c keygen.c encrypt.c decrypt.c miller-rabin.c mod-exp-function.c -lm
clean:
	rm wsu-pub-crypt;
