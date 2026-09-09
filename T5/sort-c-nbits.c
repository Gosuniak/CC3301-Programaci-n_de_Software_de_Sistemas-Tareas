#include <string.h>

void sort(unsigned int *nums, int n) {
  unsigned int *ult= &nums[n-1];
  unsigned int *p= nums;
  while (p<ult) {
    // No modifique nada arriba de esta linea
    // Inicio de la parte que debe cambiar

    unsigned int mask = (unsigned int) 1;
    int p0_ones = 0;
    int p1_ones = 0;
    for (int i = 0; i < 32; i++) {
      if (((p[0] >> i) & mask) == 1) {
        p0_ones++;
      }
      if (((p[1] >> i) & mask) == 1) {
        p1_ones++;
      }
    }

    int t1 = p0_ones >= p1_ones ? 0 : 1; // '? 0 : 1' -> si se cumple la cond, t1 = 0, si no, t1 = 1

    // Fin de la parte que debe cambiar
    // No Cambie nada mas a partir de aca
    if (t1 <= 0)
      p++;
    else {
      unsigned int tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= nums;
    }
  }
}