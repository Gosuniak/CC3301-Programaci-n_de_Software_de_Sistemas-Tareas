#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// cp cola-orig.txt cola.txt

int main(int argc, char *argv[]) {
    // Manejo de archivo
    if (argc != 2) {
        fprintf(stderr, "Uso: %s nom_arch", argv[0]);
    }

    char* filename = argv[1];
    FILE* f = fopen(filename, "r+");
    if (f == NULL) {
        perror(filename);
        exit(1);
    }

    // Caso cola vacía + registrar número de elementos n
    char nelem[16];
    fread(nelem, 1, 5, f); // f queda apuntando al primer caracter del primer elemento de la cola
    nelem[5] = '\0';
    int n = atoi(nelem);
    if (n == 0) {
        fprintf(stderr, "error: %s esta vacia\n", filename);
        exit(3);
    }

    // Recorremos la cola buscando la prioridad mayor y registramos el valor y la posición
    char buf[18];
    int prioridad = 9999;
    int pos = 0;
    for (int i = 0; i < n; i++) {
        fread(buf, 1, 17, f); // con el primer fread quedamos en la 2da línea, así que podemos leer directamente sin reubicar f
        buf[17] = '\0'; // ponemos el fin de string para poder pasarle el buf a la función atoi
        int p = atoi(buf + 10);
        if (p < prioridad) {
            prioridad = p;
            pos = i;
        }
    }

    // Mostramos el texto en pantalla
    fseek(f, 4+1+pos*(16+1), SEEK_SET); // nos posicionamos en la línea correspondiente al texto con mayor prioridad
    fread(buf, 1, 10, f); // guardamos el texto en el buffer y ponemos el 0 de fin de string
    buf[10] = '\0';
    printf("%s\n", buf);

    // Actualizamos el tamaño de la cola
    sprintf(nelem, "%-4d\n", n-1); // generamos el string "n-1    \n\0" que queda guardado en nelem
    fseek(f, 0, SEEK_SET); // nos posicionamos al principio del archivo
    fputs(nelem, f); // sobreescribimos la línea con el string guardado en nelem, pero sin el '\0'

    // Movemos el último elemento al lugar libre
    // Si la posición del elemento es igual a (n-1) -> el que imprimimos es el último -> no hacemos nada. Si no es así, tenemos que tomar el último, pos = n-1,
    // guardar la línea y sobreescribir en pos = i, donde sacamos el texto con mayor prioridad
    if (pos != n - 1) {
        fseek(f, 4+1+(n-1)*(16+1), SEEK_SET); // nos movemos a la última línea
        fread(buf, 1, 17, f); // guardamos su contenido en buf, con el fin de string '\0'
        buf[17] = '\0';

        fseek(f, 4+1+pos*(16+1), SEEK_SET); // nos movemos a la línea del texto que imprimimos y sobreescribimos su contenido sin el '\0'
        fputs(buf, f);
    }
    
    fclose(f);

    return 0;
}
