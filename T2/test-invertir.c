// test-invertir.c: Programa de prueba para la tarea 2 de PSS
// Puede modificar este archivo para fines de debugging, pero una vez
// que su tarea funcione, restaure el archivo original porque se tarea
// sera verificada con este archivo sin cambios

// includes tipicos para programas en Linux
#include <stdio.h>   // Para las funciones printf, fread, etc.
#include <stdlib.h>  // Funciones estandares de C como malloc, exit
#include <stdint.h>  // Con los tipos enteros de tamanno conocido como int32_t
#include <string.h>  // Funciones para strings como strcpy, strcmp

#include "test-util.h"
#include "invertir.h"

#define SIZE (500000000)

void test_unitario_invertir(void) {
  {
    char str[] = "the sky is blue";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "blue is sky the") != 0) {
      fprintf(stderr, "El resultado debio ser \"blue is sky the\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = "   hello   world    ";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "world hello") != 0) {
      fprintf(stderr, "El resultado debio ser \"world hello\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = "the   sky is     blue  ";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "blue is sky the") != 0) {
      fprintf(stderr, "El resultado debio ser \"blue is sky the\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = "       hello world!";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "world! hello") != 0) {
      fprintf(stderr, "El resultado debio ser \"world! hello\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = "";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "") != 0) {
      fprintf(stderr, "El resultado debio ser \"\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = " ";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "") != 0) {
      fprintf(stderr, "El resultado debio ser \"\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = "     ";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "") != 0) {
      fprintf(stderr, "El resultado debio ser \"\", no \"%s\"\n", str);
      exit(1);
    }
  }
  {
    char str[] = "  world  ";
    printf("Verificando con s = \"%s\"\n", str);
    invertir(str);
    if (strcmp(str, "world") != 0) {
      fprintf(stderr, "El resultado debio ser \"world\", no \"%s\"\n", str);
      exit(1);
    }
  }
}

void test_unitario_invertido(void) {
  {
    char str[] = "the sky is blue";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "blue is sky the") != 0) {
      fprintf(stderr, "El resultado debio ser \"blue is sky the\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "the sky is blue") != 0) {
      fprintf(stderr, "El string s debe ser \"the sky is blue\", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = "   hello   world    ";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "world hello") != 0) {
      fprintf(stderr, "El resultado debio ser \"world hello\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "   hello   world    ") != 0) {
      fprintf(stderr, "El string s debe ser \"   hello   world    \", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = "the   sky is     blue  ";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "blue is sky the") != 0) {
      fprintf(stderr, "El resultado debio ser \"blue is sky the\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "the   sky is     blue  ") != 0) {
      fprintf(stderr, "El string s debe ser \"the   sky is     blue  \", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = "       hello world!";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "world! hello") != 0) {
      fprintf(stderr, "El resultado debio ser \"world! hello\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "       hello world!") != 0) {
      fprintf(stderr, "El string s debe ser \"       hello world!\", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = "";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "") != 0) {
      fprintf(stderr, "El resultado debio ser \"\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "") != 0) {
      fprintf(stderr, "El string s debe ser \"\", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = " ";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "") != 0) {
      fprintf(stderr, "El resultado debio ser \"\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, " ") != 0) {
      fprintf(stderr, "El string s debe ser \" \", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = "     ";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "") != 0) {
      fprintf(stderr, "El resultado debio ser \"\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "     ") != 0) {
      fprintf(stderr, "El string s debe ser \"     \", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
  {
    char str[] = "  world  ";
    printf("Verificando con s = \"%s\"\n", str);
    char *res = invertido(str);
    if (strcmp(res, "world") != 0) {
      fprintf(stderr, "El resultado debio ser \"world\", no \"%s\"\n", res);
      exit(1);
    }
    if (strcmp(str, "  world  ") != 0) {
      fprintf(stderr, "El string s debe ser \"  world  \", no \"%s\"\n", str);
      exit(1);
    }
    free(res);
  }
}


void test_unitario(void) {
  printf("----- Verificando funcion invertir ------\n");
  test_unitario_invertir();
  printf("----- Verificando funcion invertidos ------\n");
  test_unitario_invertido();
}

typedef struct {
  char **res;
} Param;

char *strings[] = {"", " ", "  ", "         ", "a", "palabra", "     palabra    ", "palabra    ", "     palabra", "hola    que   tal", "    hola    que   tal    ", "hola    que   tal    ", "    hola    que   tal"};
char *results[] = {"", "", "", "", "a", "palabra", "palabra", "palabra", "palabra", "tal que hola", "tal que hola", "tal que hola", "tal que hola"};

char *enorme(int len, char **pref) {
  char *res = malloc(len + 1);
  int refLen = 0;
  {
    char *s = res;
    char *p = s, *top = p + len;
    *top = 0;
    for(;;) {
      for(char d='a'; d<='z'; d++) {
        for(int j=1; j<4; j++){
          for(int i = 0; i < j; i++) {
            *p++ = ' ';
            if(p >= top) {
              if(refLen > 0) refLen--;
              goto buildRef;
            }
          }
          for(int i = 0; i < j; i++) {
            *p++ = d;
            refLen++;
            if(p >= top) {
              goto buildRef;
            }
          }
          refLen++;
        }
      }
    }
  }

  buildRef:

  {
    char *s = malloc(refLen + 1);
    *pref = s;
    char *p = s, *top = p + refLen;
    *top-- = 0;
    for(;;) {
      for(char d='a'; d<='z'; d++) {
        for(int j=1; j<4; j++){
          if (top < p) return res;
          for(int i = 0; i < j; i++) {
            *top-- = d;
            if(top < p) {
              return res;
            }
          }
          *top-- = ' ';
        }
      }
    }
  }
}

void verify_results(void *ptr) {
  Param *parm = ptr;
  for(int i = 0; i < 13; i++) {
    char *res = parm->res[i];
    char *correct_res = results[i];
    if(strcmp(res, correct_res) != 0) {
      fprintf(stderr, "El resultado debio ser \"%s\", no \"%s\"\n", correct_res, res);
      free(parm->res[i]);
      exit(1);
    }
    free(parm->res[i]);
  }
}

void bench_serie_invertir(void *ptr) {
  char *str[13], *res[13];
  char **aux = str;
  for(int i = 0; i < 13; i++) {
    *aux = malloc(strlen(strings[i]) + 1);
    strcpy(*aux, strings[i]);
    aux++;
  }
  aux = res;
  for(int i = 0; i < 13; i++) {
    invertir(str[i]);
    *aux = malloc(strlen(str[i]) + 1);
    strcpy(*aux, str[i]);
    free(str[i]);
    aux++;
  }
  Param parm = { res };
  printf("--------------------------------------------\n");
  printf("Verificando la correctitud de los resultados de invertir\n");
  verify_results(&parm);
  printf("Ejecucion string enorme\n");
  char *ref;
  char *s= enorme(SIZE, &ref);
  invertir(s);
  if(strcmp(s, ref) != 0) {
    fprintf(stderr, "Resultado incorrecto en invertir\n");
    exit(1);
  }
  free(s);
  free(ref);
}

void bench_serie_invertido(void *ptr) {
  char *str[13], *res[13];
  char **aux = str;
  for(int i = 0; i < 13; i++) {
    *aux = malloc(strlen(strings[i]) + 1);
    strcpy(*aux, strings[i]);
    aux++;
  }
  aux = res;
  for(int i = 0; i < 13; i++) {
    char *r = invertido(str[i]);
    *aux = malloc(strlen(r) + 1);
    strcpy(*aux, r);
    free(str[i]);
    aux++;
  }
  Param parm = { res };
  printf("--------------------------------------------\n");
  printf("Verificando la correctitud de los resultados de invertido\n");
  verify_results(&parm);
  printf("Ejecucion string enorme\n");
  char *ref;
  char *s= enorme(SIZE, &ref);
  invertir(s);
  if(strcmp(s, ref) != 0) {
    fprintf(stderr, "Resultado incorrecto en invertir\n");
    exit(1);
  }
  free(s);
  free(ref);
}



static void bench_invertir(void *ptr) {
  bench_serie_invertir(ptr);
}

static void bench_invertido(void *ptr) {
  bench_serie_invertido(ptr);
}


void benchmark(int refs[], int nrefs) {
  // En tareas en donde es necesario ejecutar varios benchmarks, los
  // tiempos de referencia vienen en refs[0], refs[1], ..., refs[n-1]
  // En esta tarea hay 2 benchmarks: invertir e invertidos
  // refs[0] es el tiempo de referencia para invertir
  // refs[1] es el tiempo de refencia para invertidos
  if (refs!=NULL && nrefs!=2) {
    fprintf(stderr, "El numero de tiempos de referencia debe ser 2\n");
    exit(1);
  }
  int trefInvertido= refs==NULL ? 0 : refs[0];
  int trefInvertir = refs==NULL ? 0 : refs[0];

  printf("------------------------------------------\n");
  printf("Benchmark de invertir\n");
  char *resParmInvertir;
  Param ParmInvertir= { &resParmInvertir };
  run_bench(bench_invertir, &ParmInvertir, trefInvertir   , 80        , 5);

  printf("------------------------------------------\n");
  printf("Benchmark de invertidos\n");
  char *resParmInvertido;
  Param ParmInvertido= { &resParmInvertido };
  run_bench(bench_invertir, &ParmInvertido, trefInvertido   , 80        , 5);
}
