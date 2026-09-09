#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "test-util.h"

// ----------------------------------------------------
// Funcion que entrega el tiempo de CPU usado desde
// que se invoco rstTime()

static int time0= 0;

static int getTime0(void) {
    struct timeval Timeval;
    gettimeofday(&Timeval, NULL);
    return Timeval.tv_sec*1000+Timeval.tv_usec/1000;
}

static void rstTime(void) {
  time0= getTime0();
}

static int getTime(void) {
  return getTime0()-time0;
}

FILE *ref_file= NULL;

void run_bench( void (*fun)(void *ptr), void *ptr,
                int tiempo_ref, int tolerancia, int nintentos ) {
  if (ref_file!=NULL) {
    int tiempos[3];
    for (int k= 0; k<3; k++) {
      rstTime();
      (*fun)(ptr);
      tiempos[k]= getTime();
    }
    int med;
    // Calcular la mediana de los 3 tiempos
    if (tiempos[0]>tiempos[1]) {
      int temp= tiempos[0];
      tiempos[0]= tiempos[1];
      tiempos[1]= temp;
    }
    if (tiempos[1]<=tiempos[2])
      med= tiempos[1];
    else if (tiempos[2]<=tiempos[0])
      med= tiempos[0];
    else
      med= tiempos[2];
    fprintf(ref_file, "%d ", med);
    return;
  }

  int k= 0;
  for (;;) {
    rstTime();
    (*fun)(ptr);
    int tiempo= getTime();
    printf("Tiempo de cpu: %d milisegundos\n",
           tiempo);
    if (tiempo_ref<1)
      return;
    printf("Tiempo de cpu de la version del profesor: %d milisegundos\n",
           tiempo_ref);
    double q= (double)tiempo/(double)tiempo_ref;
    int porciento= (q-1.)*100;
    printf("Porcentaje de sobrecosto: %d %%\n", porciento);
    if (porciento<=tolerancia)
      return;
    fprintf(stderr, "*** El sobrecosto excede lo requerido ***\n");
    if (k<=nintentos)
      break;
    fprintf(stderr, "Volveremos a intentar\n");
    k++;
  }
  fprintf(stderr, "Lo siento: despues de %d intentos supera "
                  "el sobrecosto tolerado de %d %%\n",
                  nintentos, tolerancia);
  fprintf(stderr, "Coloque su computador en modo alto rendimiento, porque el\n"
                  "economizador de bateria puede alterar los resultados.\n"
                  "No ejecute este programa junto a otros programas que hagan\n"
                  "un uso intensivo de la CPU.  En windows puede lanzar el\n"
                  "administrador de tareas para verificar que el uso de CPU\n"
                  "sea bajo.\n");
  exit(1);
}

int main(int argc, char **argv) {
  if (argc>=2 && strcmp(argv[1], "ref")==0) {
    // Esta es la version del profesor
    // Hay que calcular tiempos de referencia
    ref_file= fopen("tiempo-ref.txt", "w");
    benchmark(NULL, 0);
    fclose(ref_file);
  }
  else {
    // Esta es la version del alumno
    printf("Tests unitarios\n");
    test_unitario(); // Verificar correctitud de la solucion
    printf("Test unitarios aprobados\n");
    if (argc==1) {
      // Esta es la ejecucion sin optimizar
      // Se verifica que las pruebas hechas durante el benckmark
      // arrojan resultados correctos
      benchmark(NULL, 0);
      printf("Aprobado\n");
    }
    else {
      // Esta es la ejecucion optimizada
      //
      printf("Benchmarks\n");
      int refs[argc-1];
      for (int k= 1; k<argc; k++)
      refs[k-1]= atoi(argv[k]);
      benchmark(refs, argc-1); // Verificar tiempos de ejecucion
      printf("Benchmarks aprobados\n");
    }
  }
  printf("Felicitaciones: aprobo los tests de este modo de ejecucion\n");
  return 0;
}
