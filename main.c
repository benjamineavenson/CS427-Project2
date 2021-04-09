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

  FILE* key = NULL;
  FILE* input = NULL;
  FILE* output = NULL;

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
    } else if(strcmp(argv[i], "-in") == 0) {
      input = fopen(argv[++i], "r");
      if(input == NULL){
        printf("Failed to open file %s. Terminating...\n", argv[i]);
        exit(-1);
      }
    } else if(strcmp(argv[i], "-out") == 0) {
      output = fopen(argv[++i], "w+");
      if(output == NULL){
        printf("Failed to open file %s. Terminating...\n", argv[i]);
        exit(-1);
      }
    } else if(strcmp(argv[i], "-k") == 0) {
      key = fopen(argv[++i], "r");
      if(key == NULL){
        printf("Failed to open file %s. Terminating...\n", argv[i]);
        exit(-1);
      }
    } else {
      printf("Flag not recognized: %s\nTerminating...\n", argv[i]);
      exit(-1);
    }
  }

  FILE* pubkey = NULL;
  FILE* prikey = NULL;

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
      if(key == NULL || input == NULL || output == NULL){
        printf("One or more files weren't specified. Terminating...\n");
        exit(-1);
      }
      encryption(key, input, output);
      break;
    case decrypt:
      if(key == NULL || input == NULL || output == NULL){
        printf("One or more files weren't specified. Terminating...\n");
        exit(-1);
      }
      decryption(key, input, output);
      break;
    default:
      printf("Mode not specified. Terminating...\n");
      exit(-1);
  }


}
