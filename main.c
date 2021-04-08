#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

void keygen(FILE*, FILE*);
void encryption(FILE*, FILE*, FILE*);
void decryption(FILE*, FILE*, FILE*);

int main(int argc, char** argv){
  
  enum Mode{noSelection, genkey, encrypt, decrypt};

  enum Mode selectedMode = noSelection;
  int i;
  for(i = 1; i < argc; i++){  //parse the command line args
    if(strcmp(argv[i], "-genkey") == 0) {
      if(selectedMode != noSelection){
        printf("More than one mode specified. Terminating...\n");
        exit(-1);
      }
      selectedMode = genkey;
    } else if(strcmp(argv[i], "-e") == 0) {
      if(selectedMode != noSelection){
        printf("More than one mode specified. Terminating...\n");
        exit(-1);
      }
      selectedMode = encrypt;
    } else if(strcmp(argv[i], "-d") == 0) {
      if(selectedMode != noSelection){
        printf("More than one mode specified. Terminating...\n");
        exit(-1);
      }
      selectedMode = decrypt;
    } else {
      printf("Flag not recognized: %s\nTerminating...\n", argv[i]);
      exit(-1);
    }
  }

  FILE* pubkey = NULL;
  FILE* prikey = NULL;
  FILE* plaintext = NULL;
  FILE* ciphertext = NULL;
  FILE* decipheredtext = NULL;

  switch(selectedMode){
    case genkey:
      pubkey = fopen("pubkey.txt", "w+");
      prikey = fopen("prikey.txt", "w+");
      if(pubkey == NULL){
        printf("Failed to open pubkey.txt. Terminating...\n");
        exit(-1);
      }
      if(prikey == NULL){
        printf("Failed to open prikey.txt. Terminating...\n");
        exit(-1);
      }
      keygen(pubkey, prikey);
      break;
    case encrypt:
      pubkey = fopen("pubkey.txt", "r");
      plaintext = fopen("ptext.txt", "r");
      ciphertext = fopen("ctext.txt", "w+");
      if(pubkey == NULL){
        printf("Failed to open pubkey.txt. Terminating...\n");
        exit(-1);
      }
      if(plaintext == NULL){
        printf("Failed to open ptext.txt. Terminating...\n");
        exit(-1);
      }
      if(ciphertext == NULL){
        printf("Failed to open/create ctext.txt. Terminating...\n");
        exit(-1);
      }
      encryption(pubkey, plaintext, ciphertext);
      break;
    case decrypt:
      prikey = fopen("prikey.txt", "r");
      ciphertext = fopen("ctext.txt", "r");
      decipheredtext = fopen("dtext.txt", "w+");
      if(prikey == NULL){
        printf("Failed to open prikey.txt. Terminating...\n");
        exit(-1);
      }
      if(ciphertext == NULL){
        printf("Failed to open ctext.txt. Terminating...\n");
        exit(-1);
      }
      if(decipheredtext == NULL){
        printf("Failed to open/create dtext.txt. Terminating...\n");
        exit(-1);
      }
      decryption(prikey, ciphertext, decipheredtext);
      break;
    default:
      printf("Mode not specified. Terminating...\n");
      exit(-1);
  }


}
