// test-dup.c: Programa de prueba para la tarea 1 de PSS
// Puede modificar este archivo para fines de debugging, pero una vez
// que su tarea funcione, restaure el archivo original porque se tarea
// sera verificada con este archivo sin cambios

// includes tipicos para programas en Linux
#include <stdio.h>   // Para las funciones printf, fread, etc.
#include <stdlib.h>  // Funciones estandares de C como malloc, exit
#include <stdint.h>  // Con los tipos enteros de tamanno conocido como int32_t
#include <string.h>  // Funciones para strings como strcpy, strcmp

#include "test-util.h"
#include "dup.h"

// ----------------------------------------------------
// Funcion que entrega numero aleatorio de 64 bits

static unsigned long long randull() {
  unsigned long long x = rand();
  x = (x<<31) | rand();
  x= (x<<2) | (rand() & 3);
  return x;
}

// ----------------------------------------------------
// Funcion que calcula duplicado mas largo con
// divisiones y restos

static unsigned long long divDupMasLargo(unsigned long long x) {
  int tam= 0;
  unsigned sec= 0;
  unsigned long long dos_ala_t= 2;
  unsigned long long dos_ala_2t= 4;
  for (int t= 1; t<=32; t++) {
    unsigned long long x_2t_bits= x;
    if (t!=32)
      x_2t_bits= x % dos_ala_2t;
    unsigned long long x_t_bits_sup= x_2t_bits / dos_ala_t;
    unsigned long long x_t_bits_inf= x_2t_bits % dos_ala_t;
    if (x_t_bits_sup == x_t_bits_inf) {
      tam= t;
      sec= x_t_bits_inf;
    }
    dos_ala_t *= 2;
    dos_ala_2t *= 4;
  }
  return ((unsigned long long)tam<<32) | sec;
}

// ----------------------------------------------------
// Funcion que genera n numeros aleatorios

static void gen(unsigned long long nums[], int n) {
  for (int i= 0; i<n; i++) {
    unsigned long long x= randull();
    nums[i]= x;
  }
}

void test_unitario(void) {
  { // Primera condicion de borde: no hay secuencia duplicada
    // int tam=dupMasLargo(0b1);
    // tam==0, sec==0
    printf("Verificando con x = 0b01\n");
    unsigned long long res=dupMasLargo(0x1);
    int tam= res >> 32;
    unsigned int sec= res;
    if (tam!=0) {
      fprintf(stderr, "Largo debe ser 0, no %d\n", tam);
      exit(1);
    }
    if (sec!=0x0) {
       fprintf(stderr, "sec debe ser 0x0, no %x\n", sec);
       exit(1);
    }
  }

  { // Segunda condicion de borde: la secuencia duplicada es de 32 bits
    // int tam=dupMasLargo(0b0);
    // x>>32 == 0b0
    // tam==32, sec==0b0
    printf("Verificando con x = 0b0\n");
    unsigned long long res=dupMasLargo(0x0);
    int tam= res >> 32;
    unsigned int sec= res;
    if (tam!=32) {
      fprintf(stderr, "Largo debe ser 32, no %d\n", tam);
      exit(1);
    }
    if (sec!=0x0) {
       fprintf(stderr, "sec debe ser 0x0, no %x\n", sec);
       exit(1);
    }
  }

  { // Secuencia duplicada de tamaño 1
    // int tam=dupMasLargo(0b11);
    // x>>1 == 0b1
    // tam==1, sec==0b1
    printf("Verificando con x = 0b11\n");
    unsigned long long res=dupMasLargo(0x3);
    int tam= res >> 32;
    unsigned int sec= res;
    if (tam!=1) {
      fprintf(stderr, "Largo debe ser 1, no %d\n", tam);
      exit(1);
    }
    if (sec!=0x1) {
       fprintf(stderr, "sec debe ser 0x1, no %x\n", sec);
       exit(1);
    }
  }

  {
    // int tam=dupMasLargo(0b1 0110 0100 1001 0010 0100);
    // x>>9 == 0b1011 0010 0100
    // tam==9, sec==0b1 0010 0100
    printf("Verificando con x = 0b1 0110 0100 1001 0010 0100\n");
    unsigned long long res=dupMasLargo(0x164924);
    int tam= res >> 32;
    unsigned int sec= res;
    if (tam!=9) {
      fprintf(stderr, "Largo debe ser 9, no %d\n", tam);
      exit(1);
    }
    if (sec!=0x124) {
       fprintf(stderr, "sec debe ser 0x128, no %x\n", sec);
       exit(1);
    }
  }

  { // Otra secuencia de largo 32
    //
    // x>>9 == 0b1011 0010 0100
    // tam==9, sec==0b1 0010 0100
    printf("Verificando con x = 0x3af13c803af13c80\n");
    unsigned long long xm= 0x3af13c80;
    unsigned long long res=dupMasLargo((xm<<32)|xm);
    int tam= res >> 32;
    unsigned int sec= res;
    if (tam!=32) {
      fprintf(stderr, "Largo debe ser 32, no %d\n", tam);
      exit(1);
    }
    if (sec!=xm) {
       fprintf(stderr, "sec debe ser %llx, no %x\n", xm, sec);
       exit(1);
    }
  }
}

typedef struct {
  int n;
  unsigned long long *nums, *res;
  unsigned long long (*fun)(unsigned long long x);
} Param;

static void bench_dup(void *ptr) {
  Param *parm= ptr;
  for (int k= 0; k<parm->n; k++) {
    parm->res[k]= (*parm->fun)(parm->nums[k]);
  }
}

// Se realizan mas pruebas para la version optimizada
// En esta tarea requiere 3*8*N bytes: ~ 240 MB
#ifdef OPT
#define N 10000000
#else
#define N 100000
#endif

unsigned long long nums[N], divRes[N], bitsRes[N];

void benchmark(int refs[], int nrefs) {
  // En tareas en donde es necesario ejecutar varios benchmarks, los
  // tiempos de referencia vienen en refs[0], refs[1], ..., refs[n-1]
  // En esta tarea hay 2 benchmarks: con divisiones/multiplicaciones y con bits
  // refs[0] es el tiempo de referencia con divisiones/multiplicaciones
  //         y no se usa
  // refs[1] es el tiempo de refencia con bits de la version del profesor
  //         con este se compara la version del alumno
  if (refs!=NULL && nrefs!=2) {
    fprintf(stderr, "El numero de tiempos de referencia debe ser 2\n");
    exit(1);
  }

  int n= N;

  printf("------------------------------------------\n");
  printf("Benchmark: Se generan %d numeros aleatorios\n", n);
  printf("Los primeros numeros son:\n");
  gen(nums, n);
  for (int i= 0; i< (n>12 ? 12 : n); i++) {
    printf("%llx ", nums[i]);
    if ((i+1)%4==0)
      printf("\n");
  }
  printf("\n");

  printf("Se calcula el tiempo de calculo del duplicado mas largo\n");
  printf("con divisiones, restos y multiplicaciones\n");
  Param divParm= { n, nums, divRes, divDupMasLargo };
  // Este benchmark es solo para calcular los resultados correctos
  // y por lo tanto no hay tiempo de referencia
  //        fun      , ptr     , tiempo_ref, tolerancia, nintentos
  run_bench(bench_dup, &divParm, 0         , -1        , 1);

  printf("--------------------------------------------------------\n");
  printf("Benchmark: Para los mismos numeros aleatorios se calcula\n");
  printf("el tiempo de calculo del duplicado mas largo utilizando\n");
  printf("la version de dupMasLargo que Ud. programo\n");
  int tref= refs==NULL ? 0 : refs[1];
  Param bitsParm= { n, nums, bitsRes, dupMasLargo };
  //        fun      , ptr      , tiempo_ref, tolerancia, nintentos
  run_bench(bench_dup, &bitsParm, tref   , 80        , 5);

  printf("--------------------------------------------\n");
  printf("Verificando la correctitud de los resultados\n");
  for (int k= 0; k<n; k++) {
    if (divRes[k]!=bitsRes[k]) {
      fprintf(stderr, "dupMasLargo(0x%llx) es incorrecto\n",
                      nums[k]);
      fprintf(stderr, "el resultado es: 0x%llx\n", bitsRes[k]);
      fprintf(stderr, "debio ser:       0x%llx\n", divRes[k]);
      exit(1);
    }
  }
}
