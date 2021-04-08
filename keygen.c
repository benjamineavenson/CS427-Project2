#include <stdio.h>
#include <time.h>
#include <stdlib.h>

_Bool millerRabin(unsigned int, int);
unsigned int modExp(long long int, long long int, unsigned int);

void keygen(FILE* pub, FILE* pri){
  long long int g = 2;  //choose our generator to be 2
  unsigned int p;
  unsigned int q;

  time_t seed;  //grab the current unix time to seed our random number generator
  time(&seed);
  srand(seed);

  while(1){
    while(1){
      q = rand(); //on my machine this generates a number between 0 and 2^31, so a 31 bit number
      printf("checking %u\n", q);
      if(q%12 == 5 && millerRabin(q, 3)) break;  //make sure our random number is prime and congruent to 5 mod 12
    }
    printf("found an acceptable q\n");
    p = (2*q) + 1;
    if(millerRabin(p, 3)) break; //we calculate p from q and make sure its prime.
  }

  printf("found an acceptable p\n");

  long long int d = rand(); //choose a random number greater than 0 and less than p
  d = d%(p-1);
  d++;

  unsigned int e = modExp(g, d, p); //calculate the modular inverse for the public key

  fprintf(pub, "%u %lli %u", p, g, e);  //output our keys
  printf("public key: %u %lli %u\n", p, g, e);
  fprintf(pri, "%u %lli %lli", p, g, d);
  printf("private key: %u %lli %lli\n", p, g, d);
  
  fclose(pub);
  fclose(pri);
  exit(0);
}
  
  
