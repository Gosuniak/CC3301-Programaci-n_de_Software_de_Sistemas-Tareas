#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertir.h"

void invertir(char* s) {
  // Primero invertimos el string: "hola que tal" -> "lat euq aloh"
  char* front = s;
  char* back = s + strlen(s) - 1; // creamos punteros al principio y al final del string
  while (front < back) { // mientras los punteros no se encuentren
      char aux = *front; // guardamos el caracter al que apunta front en una variable
      *front = *back; // actualizamos el caracter al que apunta front por el que apunta back
      *back = aux; // actualizamos el caracter al que apunta back por el que apuntaba front, guardado en aux
      front++; // movemos front hacia el final
      back--; // movemos back hacia el principio
  }

  // Luego, eliminamos espacios extra
  char* copy = s;
  char* check = s;

  while (*check != 0) { // Recorremos el string s
      while (*check == ' ') { // Saltamos los espacios del principio
          check++;
      }
      if (*check == 0) { // Chequeamos que no estemos en el fin de string al saltarnos los espacios (ej: s = "     ")
          break;
      }
      while (*check != 0 && *check != ' ') { // Mientras no estemos en el fin de string y check no apunte a un espacio, copiamos caracteres
          *copy = *check;
          copy++;
          check++;
      }
      while (*check == ' ') { // Saltamos los espacios entre palabras
          check++;
      }
      if (*check != 0) { // Si es que hay más palabras, agregamos un espacio y movemos copy
          *copy = ' ';
          copy++;
      }
  }
  *copy = 0; // Colocamos el fin de string

  // Y finalmente, invertimos palabra por palabra
  check = s;

  while (*check != 0) { // Recorremos el string s
      while (*check == ' ') { // Nos saltamos los espacios (es para saltarnos los espacios entre palabras)
          check++;
      }
      if (*check == 0) { // Si nos saltamos los espacios y llegamos al final (s = "    "), termina
          break;
      }
      char* inicio_palabra = check; // Creamos un puntero que apunta al primer caracter de una palabra (al saltarse los espacios, check termina apuntando a una palabra)
      while (*check != 0 && *check != ' ') { // Mientras check no apunte al fin de string y no apunte a un espacio, avanza (recorremos la palabra)
          check++;
      }
      char* fin_palabra = check - 1; // Creamos un puntero que apunta al último caracter de una palabra
      while (inicio_palabra < fin_palabra) { // Invertimos la palabra intercambiando los caracteres del principio con los del final
          char aux2 = *inicio_palabra;
          *inicio_palabra = *fin_palabra;
          *fin_palabra = aux2;
          inicio_palabra++;
          fin_palabra--;
      }
  }
}

char *invertido(char* s) {
  // Hacemos una copia del string s
  char* copia = malloc(strlen(s) + 1); 
  strcpy(copia, s);

  // Aplicamos invertir en el string copiado para no modificar s
  invertir(copia);

  // Hacemos una copia del string copia
  char* string = malloc(strlen(copia) + 1);
  strcpy(string, copia);

  // Liberamos la memoria de copia y devolvemos el string final
  free(copia);
  return string;
}
