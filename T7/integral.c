#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "integral.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
  int fds[p][2];       // fds[i][0]: lectura, fds[i][1]: escritura
  pid_t pids[p];

  double h = (xf - xi) / p;  // Longitud de cada subintervalo
  int n_local = n / p;       // Número de trapecios que calcula cada proceso

  // Crear procesos hijos
  for (int i = 0; i < p; i++) {
      pipe(fds[i]);           // Crear pipe para comunicar con el hijo
      pids[i] = fork();       // Crear proceso

      if (pids[i] == 0) {
          // === Código ejecutado por el hijo ===
          close(fds[i][0]);   // El hijo no lee, solo escribe

          // Calcular límites del subintervalo
          double local_xi = xi + i * h;
          double local_xf = (i == p - 1) ? xf : local_xi + h;  // El último hijo ajusta el final

          // Calcular integral en el subintervalo y enviar resultado al padre
          double res = integral(f, ptr, local_xi, local_xf, n_local);
          write(fds[i][1], &res, sizeof(double));
          close(fds[i][1]);   // Cierra el extremo de escritura

          exit(0);            // Termina el proceso hijo
      } else {
          // === Código ejecutado por el padre ===
          close(fds[i][1]);   // El padre no escribe, solo lee
      }
  }

  // Recoger resultados de cada hijo
  double total = 0;
  for (int i = 0; i < p; i++) {
      double parcial;
      read(fds[i][0], &parcial, sizeof(double)); // Leer resultado parcial
      close(fds[i][0]);                          // Cierra lectura de la tubería
      waitpid(pids[i], NULL, 0);                 // Espera a que el hijo termine
      total += parcial;                          // Acumula resultado
  }

  return total;
}
