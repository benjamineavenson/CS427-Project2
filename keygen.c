#include <stdio.h>
#include <time.h>
#include <stdlib.h>

_Bool millerRabin(unsigned int, int);
unsigned long long int modExp(long long int, long long int, unsigned int);

void keygen(FILE* pub, FILE* pri){
  unsigned long long int g = 2;  //choose our generator to be 2
  unsigned long long int p;
  unsigned long long int q;

  time_t seed;  //grab the current unix time to seed our random number generator
  time(&seed);
  srand(seed);


  q = rand(); //on my machine this generates a number between 0 and 2^31, so a 31 bit number...
  q = 0x40000000;
  q = q | 0x40000000; //lets set the 31st bit, just to make sure its a 31 bit number so our generated prime is 32-bit

  while(1){
    while(1){
      q++;
      if(q >= 0x80000000){
        printf("repeating...\n");
        q = 0x40000000;
      }
      if(q%12 == 5 && millerRabin(q, 3)) break;  //make sure our random number is prime and congruent to 5 mod 12
    }
    p = (q << 1) + 1;
    if(millerRabin(p, 3)) break; //we calculate p from q and make sure its prime.
  }

  unsigned long long int d = rand(); //choose a random number greater than 0 and less than p
  d = d%(p-1);
  d++;

  unsigned long long int e = modExp(g, d, p); //calculate the modular inverse for the public key

  fprintf(pub, "%llu %llu %llu", p, g, e);  //output our keys
  printf("public key: %llu %llu %llu\n", p, g, e);
  fprintf(pri, "%llu %llu %llu", p, g, d);
  printf("private key: %llu %llu %llu\n", p, g, d);
  
  fclose(pub);
  fclose(pri);
  exit(0);
}
  
  
