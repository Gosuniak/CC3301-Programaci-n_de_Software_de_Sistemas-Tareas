#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sort.h"

// Muestra un numero en binario en la salida estandar

void printBin(uint x) { 
  printf("0b");
  int bits[sizeof(uint)*8];
  int i= 0;
  for (;;) {
    bits[i]= x&1;
    x >>= 1;
    if (x==0) 
      break;
    i++;
  }
  do {
    printf("%d", bits[i--]);
  } while (i>=0);
}

void help(int line, int i, int j) {
  printf("Para depurar use este comando para depurar sort-rv-nbits.s:\n");
  printf("make sort-c-nbits.ddd\n");
  printf("Para depurar sort-c-nbits.c use este otro comando:\n");
  printf("make sort-rv-nbits.ddd\n");
  printf("Ingrese estos comandos en el panel de comandos de ddd:\n");
  printf("break test-sort.c:%d\n", line);
  printf("cond 3 i==%d && j==%d\n", i, j);
  printf("continue\n");
  printf("Abra el panel de assembler seleccionando View -> "
         "Machine Code Window\n");
  printf("Avance con stepi hasta entrar a sort-rv-max.s\n");
  printf("Enseguida depure con stepi para avanzar lentamente\n");
  printf("El arreglo es pequenno, no va a demorarse mucho\n");
  exit(1);
}

#define N 12

int main(int argc, char *argv[]) {
  int refs[]= {
                0b0,          // 0
                0b10,         // 1
                0b101,        // 2
                0b10101,      // 3
                0b111001,     // 4
                0b11111,      // 5
                0b101010101010,   // 6
                0b100110011101,   // 7
                0b10000000000000000000000001111111, // 8
                0b11111111100000000000000000000000, // 9
                0b10101010101010101010101010101010, // 16
                0b11111111111111111111111111111111, // 32
              };

  printf("Multiples tests con arreglos de solo 2 numeros\n");

  for (int i= 0; i<N-1; i++) {
    for (int j= i+1; j<N; j++) {
      uint nums[]={refs[j], refs[i]};
      sort(nums, 2);
      if (nums[0]!=refs[j] || nums[1]!=refs[i]) {
        printf("El ordenamiento falla para el arreglo:\n");
        printBin(refs[j]); printf("   "); printBin(refs[i]); printf("\n");
        printf("El resultado fue:\n");
        printBin(nums[0]); printf("   "); printBin(nums[1]); printf("\n");
        help(65, i, j);
      }
      uint nums2[]={refs[i], refs[j]};
      sort(nums2, 2);
      if (nums2[0]!=refs[j] || nums2[1]!=refs[i]) {
        printf("El ordenamiento falla para el arreglo:\n");
        printBin(refs[i]); printf("   "); printBin(refs[j]); printf("\n");
        printf("El resultado fue:\n");
        printBin(nums[0]); printf("   "); printBin(nums[1]); printf("\n");
        help(74, i, j);
      }
    }
  }

  printf("Aprobado\n");

  printf("Ahora un arreglo de 12 numeros\n");
  uint nums[]= {
                0b101010101010, // 6
                0b10101,      // 3
                0b10,         // 1
                0b11111111100000000000000000000000, // 9
                0b100110011101, // 7
                0b101,        // 2
                0b10101010101010101010101010101010, // 16
                0b11111111111111111111111111111111, // 32
                0b10000000000000000000000001111111, // 8
                0b0,          // 0
                0b11111,      // 5
                0b111001,     // 4
               };


  printf("El arreglo desordenado es:\n");
  printf("--------------------------\n");
  for (int i= 0; i<N; i++) {
    printBin(nums[i]); printf("\n");
  }
  sort(nums, N);
  printf("\n");
  printf("El arreglo ordenado es:\n");
  printf("-----------------------\n");
  for (int i= 0; i<N; i++) {
    printBin(nums[i]); printf("\n");
  }
  for (int i= 0; i<N; i++) {
    if (nums[i]!=refs[N-i-1]) {
      fprintf(stderr, "El %d-esimo elemento es incorrecto\n", i);
      exit(1);
    }
  }

  printf("Felicitaciones: todos los tests aprobados\n");
  return 0;
}
