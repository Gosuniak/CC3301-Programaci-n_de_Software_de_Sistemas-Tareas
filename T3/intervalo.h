typedef struct nodo {
  int id;
  struct nodo *izq, *der;
} Nodo;

void elimIntervalo(Nodo **pa, int inf, int sup);
