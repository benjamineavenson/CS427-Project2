#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define false 0
#define true 1
#define PRIME 1
#define COMPOSITE 0

unsigned int modExp(long long int, long long int, unsigned int);
int millerRabinCheck(unsigned int, long long int, long long int, long long int);

_Bool millerRabin(unsigned int n, int s){  //we are given a number to check and the number of random checks to make

  int k = 0;
  int q = n-1;

  while(q%2 == 0){  //generate k and q for miller-rabin algo
    k++;
    q = q/2;
  }

  time_t t;
  srand((unsigned int)time(&t));

  long long int a;
  for(int i = 0; i != s; i++){  //make s miller-rabin checks
    a = (rand()%(n-2)) + 1;
    if(millerRabinCheck(n, k, q, a) == COMPOSITE){  //if it ever comes up composite, we know for certain that its composite
      return 0;
    }
  }
  return 1; //if we make enough checks, we can assume its prime if it never comes up composite
} 


int millerRabinCheck(unsigned int n, long long int k, long long int q, long long int a){ //miller rabin algorithm
  if(modExp(a, q, n) == 1){
    return PRIME;
  }
  for(int i = 0; i < k; i++){
    if(modExp(a, pow(2, i)*q, n) == (n-1)){
      return PRIME;
    }
  }
  return COMPOSITE;
}
  
