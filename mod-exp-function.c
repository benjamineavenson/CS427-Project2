//calculates a^b (mod n)
#include <stdio.h>
#include <math.h>

unsigned long long int modExp(unsigned long long int a, unsigned long long int b, unsigned long long int n){
  unsigned long long int val = 1;
  unsigned int bits = (unsigned int)log2(b)+1;
  for(int i = bits-1; i >= 0; i--){
    val = (val*val)%n;
    if((b>>i)&1){
      val = (val*a)%n;
    }
  }
  return val;
}
