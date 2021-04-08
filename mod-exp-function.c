//calculates a^b (mod n)
#include <stdio.h>
#include <math.h>

unsigned long long int modExp(long long int a, long long int b, unsigned int n){
  unsigned long long int val = 1;
  unsigned int bits = (unsigned int)log2(b)+1;
  printf("bits: %u\n", bits);
  for(int i = bits-1; i >= 0; i--){
    val = (val*val)%n;
    if((b>>i)&1 == 1){
      val = (val*a)%n;
    }
  }
  return val;
}
