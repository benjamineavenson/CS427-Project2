#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define false 0
#define true 1
#define PRIME 1
#define COMPOSITE 0

unsigned long long int modExp(unsigned long long int, unsigned long long int, unsigned long long int);
int millerRabinCheck(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);

_Bool millerRabin(unsigned long long int n, int s){  //we are given a number to check and the number of random checks to make

  unsigned long long int k = 0;
  unsigned long long int q = n-1;

  while(!(q&1)){  //generate k and q for miller-rabin algo
    k++;
    q = q >> 1;
  }

  unsigned long long int a;
  for(int i = 0; i != s; i++){  //make s miller-rabin checks
    a = (rand()%(n-2)) + 1;
    if(millerRabinCheck(n, k, q, a) == COMPOSITE){  //if it ever comes up composite, we know for certain that its composite
      return 0;
    }
  }
  return 1; //if we make enough checks, we can assume its prime if it never comes up composite
} 


int millerRabinCheck(unsigned long long int n, unsigned long long int k, unsigned long long int q, unsigned long long int a){ //miller rabin algorithm
  unsigned long long int prev_x = modExp(a, q, n);
  unsigned long long int curr_x;
  for(int i = 1; i <= k; i++){
    curr_x = modExp(prev_x, 2, n);
    if(prev_x != 1 && prev_x != n-1 && curr_x == 1){
      return COMPOSITE;
    }
    prev_x = curr_x;
  }
  if(curr_x != 1) return COMPOSITE;
  
  return PRIME;
}
  
