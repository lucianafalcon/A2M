#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector *split(char *texto, char separador) {
  int i = 0, j = 0;
  char vector_auxiliar[100];

  if (texto == NULL)
    return NULL;

  struct vector *v = malloc(sizeof(struct vector));
  v->palabras = calloc(10, sizeof(char *));
  v->cantidad = 0;

  while (texto[i] != '\0') {
    if (texto[i] != separador) {
      vector_auxiliar[j] = texto[i];
      j++;
    } else {
      if (j > 0) {
        vector_auxiliar[j] = '\0';
        v->palabras[v->cantidad] = malloc((size_t)(j + 1) * sizeof(char));
        strcpy(v->palabras[v->cantidad], vector_auxiliar);
        v->cantidad++;
        j = 0;
      }
    }
    i++;
  }

  if (j > 0) {
    vector_auxiliar[j] = '\0';
    v->palabras[v->cantidad] = malloc((size_t)(j + 1) * sizeof(char));
    strcpy(v->palabras[v->cantidad], vector_auxiliar);
    v->cantidad++;
  }

  return v;
}

void vector_destruir(struct vector *v) {
  for (int i = 0; i < v->cantidad; i++) {
    free(v->palabras[i]);
  }
  free(v->palabras);
  free(v);
}

/*int main() {
  char texto[] = "hola;1;2;3";
  char separador = ';';
  int i=0;

  struct vector *v = split(texto, separador);

  if (v == NULL) {
    printf("error split\n");
  }

  for (i = 0; i < v->cantidad; i++) {
    printf("Palabra %d: %s\n", i, v->palabras[i]);
  }

  vector_destruir(v);

  return 0;
}*/
