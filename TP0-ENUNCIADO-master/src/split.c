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
    if (!v)
      return NULL;

    v->palabras = malloc(capacidad, sizeof(char *));
    v->cantidad = 0;

    while (texto[i] != '\0') {
      if (texto[i] != separador) {
        vector_auxiliar[j] = texto[i];
        j++;
      } else {
        buffer[j] = '\0';

        if (v->cantidad >= capacidad) {
          capacidad *= 2;
          char **temp = realloc(v->palabras, capacidad * sizeof(char *));
          if (!temp)
            return v;
          v->palabras = tmp;
        }

        v->palabras[v->cantidad] = malloc((j + 1) * sizeof(char));
        strcpy(v->palabras[v->cantidad], vector_auxiliar);
        v->cantidad++;
        j = 0;
      }
      i++;
    }

    if (v->cantidad >= capacidad) {
      capacidad *= 2;
      char **temp = realloc(v->palabras, capacidad * sizeof(char *));
      if (!temp)
        return v;
      v->palabras = tmp;
    }

    v->palabras[v->cantidad] = malloc((j + 1) * sizeof(char));
    strcpy(v->palabras[v->cantidad], vector_auxiliar);
    v->cantidad++;

    return v;
}

void vector_destruir(struct vector *v) {
    if (!v)
      return;

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
