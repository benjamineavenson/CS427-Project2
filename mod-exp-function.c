//calculates a^b (mod n)
#include <stdio.h>

unsigned int modExp(long long int a, long long int b, unsigned int n){
  unsigned int val = 1;
  printf("%lli\n", b);
  for(long long int i = 1; i <= b; i++){
    val = (val*a)%n;
  }
  return val;
}
