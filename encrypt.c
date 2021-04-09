#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

unsigned int modExp(long long int, long long int, unsigned int);
void encrypt_block(unsigned int, unsigned long int, unsigned long int, unsigned long int, FILE*);

void encryption(FILE* key, FILE* ptext, FILE* ctext){

  char* key_buffer = NULL;
  size_t n = 0;
  getline(&key_buffer, &n, key);  //read the key
  
  unsigned long int p;
  unsigned long int g;
  unsigned long int e;

  char* p_str;
  char* g_str;
  char* e_str;

  p_str = strtok(key_buffer, " ");  //parse the key into its tokens
  p = strtoul(p_str, NULL, 10);

  g_str = strtok(NULL, " ");
  g = strtoul(g_str, NULL, 10);

  e_str = strtok(NULL, " ");
  e = strtoul(e_str, NULL, 10);

  free(key_buffer);
  fclose(key);

  time_t seed;  //seed the random number generator
  time(&seed);
  srand(seed);

  unsigned long int buffer = 0;  //buffer to hold our bitstream
  int stored = 0; //number of bits currently stored
  unsigned long int read_byte = 0; //last read byte
  unsigned int block; //block to be encrypted
  int status; //status to be checked after reads to see if EOF has been reached
  while(1){
    while(stored < 31){ //while we need more bits for our block
      read_byte = 0;
      status = fread(&read_byte, 1, 1, ptext); //grab another byte
      if(status == 0)break;//break out of the loops if there is no more to be read
      read_byte = read_byte << (sizeof(unsigned long int)*8 - (stored + 8));  //shift it into position
      buffer = buffer | read_byte; //and place it in the buffer
      stored += 8;
    }
    block = buffer >> (sizeof(unsigned long int)*8 - 31); //get the next 31 bits from the buffer
    buffer = buffer << 31;  //shift the buffer up 31
    stored -= 31;

    encrypt_block(block, p, g, e, ctext);
    if(status == 0)break; //break out of the loops if there is no more to be read
  }
  //at this point we have some number of bits that need to be padded...
  //ive got no clue which direction to pad in, so for now i'll do nothing
  printf("buffer: %lx\n", buffer);
  printf("stored: %i\n", stored);
  
  
  fclose(ptext);
  fclose(ctext);

  exit(0);
  
}

void encrypt_block(unsigned int block, unsigned long int p, unsigned long int g, unsigned long int e, FILE* ctext){
  unsigned int c1;
  unsigned int c2;

  long long int k = rand()%p;

  c1 = modExp((long long int)g, k, (unsigned int)p);
  c2 = ((modExp((long long int)e, k, (unsigned int)p) * (block%p)) % p);

  printf("%u %u\n", c1, c2);
  fprintf(ctext, "%u %u\n", c1, c2);
}
