#CS427-Project2

##Benjamin Eavenson

##benjamin.eavenson@wsu.edu

##FILES

decrypt.c          : Decryption algorithm

encrypt.c          : Encryption algorithm

keygen.c           : Key generation algorithm

main.c             : Command line argument parsing

Makefile           : Makefile for compilation

miller-rabin.c     : Contains the function for miller-rabin primality testing

mod-exp-function.c : Contains the function for fast modular exponentiation

README.md          : Thats the file you're reading right now


##HOW TO COMPILE

While in the same directory as all of the above files, run `make`.

This will generate the executable `wsu-pub-crypt`.

Running `make clean` will remove the executable file.


##HOW TO RUN

###KEY GENERATION

To generate the public and private keys, run `./wsu-pub-crypt -genkey`.

This will create the files `pubkey.txt` and `prikey.txt`, containing the

public and private keys respectively.


###ENCRYPTION

To encrypt a plaintext file, run `./wsu-pub-crypt -e -in \<plaintext\> -out \<ciphertext\> -k \<public key file\>`.

This will encrypt the input file using the specified key, and print the resulting encryption to the screen and the output file.


###DECRYPTION

To decrypt a ciphertext file, run `./wsu-pub-crypt -d -in \<ciphertext\> -out \<decryptedtext\> -k\<private key file\>`.

This will decrypt the input file using the specified key, and print the resulting decryption to the screen and the output file.


