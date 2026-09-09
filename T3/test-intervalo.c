#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "intervalo.h"
#include "test-util.h"

// ----------------------------------------------------
// Funcion que verifica que 2 arboles binarios son iguales

static void comparar(Nodo *a, Nodo *b) {
  if (a==NULL) {
    if (b==NULL)
      return;
    fprintf(stderr, "Arboles distintos: a es NULL, b tiene etiqueta %d\n",
                    b->id);
    exit(1);
  }
  else if (b==NULL) {
    fprintf(stderr, "Arboles distintos: b es NULL, a tiene etiqueta %d\n",
                    a->id);
    exit(1);
  }
  else {
    if (a->id!=b->id) {
      fprintf(stderr, "Etiquetas de arboles son distintas: %d != %d\n",
                      a->id, b->id);
      exit(1);
    }
    comparar(a->izq, b->izq);
    comparar(a->der, b->der);
  }
}

// ----------------------------------------------------
// Funcion que verifica que los campos id de un arbol binario
// desbalanceado sea 1, 2, 3, etc.  Ademas la direccion del ultimo nodo
// debe ser ult

static void verificar_des(Nodo *a, int N, Nodo *ult) {
  int ref= 1;
  while (a->der!=NULL) {
    if (a->id!=ref) {
      fprintf(stderr, "Id es %d, debio ser %d\n", a->id, ref);
      exit(1);
    }
    if (a->izq!=NULL) {
      fprintf(stderr, "Subarbol izquierdo debio ser NULL en nodo %d\n", a->id);
      exit(1);
    }
    a= a->der;
    ref++;
  }
  if (a!=ult) {
    fprintf(stderr, "El ultimo nodo es incorrecto\n");
    exit(1);
  }
  if ( a->id != ref ) {
    fprintf(stderr, "Ultimo nodo tiene id %d, debio ser %d\n", a->id, ref);
    exit(1);
  }
}

// ----------------------------------------------------
// Libera un arbol binario

static void liberar(Nodo *a) {
  if (a!=NULL) {
    liberar(a->izq);
    liberar(a->der);
    free(a);
  }
}

// ----------------------------------------------------
// Libera un arbol binario desbalanceado.  Liberarlo con la
// la funcion liberar provocaria un desborde de pila.

static void liberar_des(Nodo *a) {
  while (a!=NULL) {
    Nodo *der= a->der;
    free(a);
    a= der;
  }
}

// ----------------------------------------------------
// Crea una copia de un arbol binario

static Nodo *copia(Nodo *a) {
  if (a==NULL)
    return NULL;
 
  Nodo *an= malloc(sizeof(Nodo));
  an->id= a->id;
  an->izq= copia(a->izq);
  an->der= copia(a->der);
  return an;
}

// ----------------------------------------------------
// Crea un arbol binario de busqueda bien equilibrado en donde 
// los id van de i a j

static Nodo *equilibrado(int i, int j) {
  if (i>j)
    return NULL;
  int k= (i+j+1)/2;
  Nodo *a= malloc(sizeof(Nodo));
  a->id= k;
  a->izq= equilibrado(i, k-1);
  a->der= equilibrado(k+1, j);
  return a;
}

// ----------------------------------------------------
// El arbol binario del enunciado

static Nodo n1= { 1, NULL, NULL };
static Nodo n3= { 3, NULL, NULL };
static Nodo n2= { 2, &n1, &n3 };

static Nodo n5= { 5, NULL, NULL };
static Nodo n6= { 6, &n5, NULL };

static Nodo n4= { 4, &n2, &n6 };

void test_unitario(void) {
  // printf("-----------------------------------------------------\n\n");

  {
    printf("Verificando el arbol vacio\n");
    Nodo *a= NULL;
    elimIntervalo(&a, 0, 0);
    comparar(a, NULL);
  }

  {
    printf("Verificando arbol de 3 nodos eliminando (1,1)\n");
    printf("Eliminando solo en subarbol izquierdo\n");
    static Nodo res_u1 = { 2, NULL, &n3 };
    Nodo *a= copia(&n2);
    elimIntervalo(&a, 1, 1);
    comparar(a, &res_u1);
    liberar(a);
  }

  {
    printf("Verificando arbol de 3 nodos eliminando (1,2)\n");
    printf("Eliminando raiz y subarbol izquierdo\n");
    static Nodo res_u2 = { 3, NULL, NULL };
    Nodo *a= copia(&n2);
    elimIntervalo(&a, 1, 2);
    comparar(a, &res_u2);
    liberar(a);
  }

  {
    printf("Verificando arbol de 3 nodos eliminando (3,3)\n");
    printf("Eliminando solo subarbol derecho\n");
    static Nodo res_u3 = { 2, &n1, NULL };
    Nodo *a= copia(&n2);
    elimIntervalo(&a, 3, 3);
    comparar(a, &res_u3);
    liberar(a);
  }

  {
    printf("Verificando arbol de 3 nodos eliminando (2,3)\n");
    printf("Eliminando raiz y subarbol derecho\n");
    static Nodo res_u4 = { 1, NULL, NULL };
    Nodo *a= copia(&n2);
    elimIntervalo(&a, 2, 3);
    comparar(a, &res_u4);
    liberar(a);
  }

  {
    printf("Verificando arbol de 3 nodos eliminando (1,3)\n");
    printf("Eliminando todo el arbol\n");
    Nodo *a= copia(&n2);
    elimIntervalo(&a, 1, 3);
    comparar(a, NULL);
    liberar(a);
  }

  {
    printf("Verificando ejemplo del enunciado\n");
    static Nodo new_n6 = { 6, NULL, NULL };
    static Nodo res_u6 = { 2, &n1, &new_n6 };
    Nodo *a= copia(&n4);
    elimIntervalo(&a, 3, 5);
    comparar(a, &res_u6);
    liberar(a);
  }

  {
    int n= 100000;
    printf("Verificando un arbol de 100 mil nodos\n");
    printf("Eliminando (25001, 100000)\n");
    printf("-------------------------------------\n\n");
    Nodo *a= equilibrado(1, n);
    int corte = n/4;
    Nodo *res = equilibrado(1, corte);
    elimIntervalo(&a, corte+1, n);
    comparar(a, res);
    liberar(a);liberar(res);
    printf("Aprobado\n");
  }
}

#ifdef OPT
#define N 20000000
#else
#define N 500000
#endif

typedef struct {
  Nodo *a;
} Param;

static void init_intervalo(void *ptr) {
  Param *p= ptr;
  p->a= equilibrado(1, N);
}

static void clean_intervalo(void *ptr) {
  Param *p= ptr;
  if (p->a!=NULL) {
    fprintf(stderr, "No elimino todo el arbol\n");
    exit(1);
  }
  liberar(p->a);
}

static void bench_intervalo(void *ptr) {
  Param *p= ptr;
  elimIntervalo(&p->a, 1, N);
}

void benchmark(int refs[], int n) {
  Param p;
  printf("\n");
  printf("=========================\n");
  printf("Benchmark de desbalancear\n");
  printf("=========================\n");
  //        prologo            benchmark           clean up
  run_bench(init_intervalo, bench_intervalo, clean_intervalo,
  //        ptr, tiempo_ref,    tolerancia, nintentos
            &p ,  refs[0]  ,        80    ,    5 );

}
