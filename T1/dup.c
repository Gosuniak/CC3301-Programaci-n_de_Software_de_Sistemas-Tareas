#include <stdio.h>
#include <stdlib.h>

#include "dup.h"

unsigned long long dupMasLargo(unsigned long long x) {
  // ... programe aca la funcion pedida ...
  unsigned long long largo = 0;
  unsigned long long patron = 0;
  unsigned long long m = (unsigned long long) -1;
  int size = (sizeof(x) << 3) >> 1;
  for (int i = 1; i <= size; i++) {
      unsigned long long mask = ~(m << i);
      if ((x & mask) == ((x >> i) & mask)) {
          largo = i;
          patron = x & mask;
      }
  }
  return (largo << 32) | patron;
}
