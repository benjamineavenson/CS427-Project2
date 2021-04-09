#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

unsigned long long int modExp(long long int, long long int, unsigned int);
unsigned int decrypt_block(unsigned long int, unsigned long int, unsigned long int, unsigned long int);

void decryption(FILE* key, FILE* ctext, FILE* dtext){

  char* key_buffer = NULL;
  size_t n = 0;
  getline(&key_buffer, &n, key); //read the key

  unsigned long int p;
  unsigned long int d;
  
  char* p_str;
  char* d_str;

  p_str = strtok(key_buffer, " ");  //parse the key into its tokens
  p = strtoul(p_str, NULL, 10);

  strtok(NULL, " ");  //skip over g, we dont need g

  d_str = strtok(NULL, " ");
  d = strtoul(d_str, NULL, 10);

  free(key_buffer);
  fclose(key);

  char* cipher_buffer = NULL;
  char* c1_str;
  char* c2_str;
  unsigned long int c1;
  unsigned long int c2;
  n = 0;


  unsigned long int buffer = 0; //buffer to hold our bitstream
  int stored = 0; //number of bits currently stored
  unsigned long int decrypted_bits;
  char writing_byte = 0;
  int status;

  while(1){
    if(stored < 8){
      status = getline(&cipher_buffer, &n, ctext);  //get the next line of ciphertext
      if(status == -1)break;  //EOF, break out of loop
      c1_str = strtok(cipher_buffer, " ");  //parse the ciphertext
      c2_str = strtok(NULL, " ");
      c1 = strtoul(c1_str, NULL, 10);
      c2 = strtoul(c2_str, NULL, 10);
      free(cipher_buffer);
      cipher_buffer = NULL;

      decrypted_bits = (unsigned long int)decrypt_block(c1, c2, p, d);  //decrypt the block represented by this line
      decrypted_bits = decrypted_bits << (sizeof(unsigned long int)*8 - (stored + 31)); //shift the bits into position for the buffer...
      buffer = buffer | decrypted_bits; //put the bits into the buffer
      stored += 31;
    }
      writing_byte = buffer >> (sizeof(unsigned long int)*8 - 8); //get the next byte to write
      buffer = buffer << 8;  //shift the buffer up 8
      stored -= 8;

      fprintf(dtext, "%c", writing_byte);
      printf("%c", writing_byte);
  }
  
  fclose(ctext);
  fclose(dtext);
  
  exit(0);
}

unsigned int decrypt_block(unsigned long int c1, unsigned long int c2, unsigned long int p, unsigned long int d){
  unsigned int m;
  m = ((modExp((long long int)c1, (long long int)((p - 1) - d), (unsigned int)p))*(c2%p))%p;
  return m;
}
