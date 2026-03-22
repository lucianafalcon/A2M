#include "split.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 10

struct vector *split(char *texto, char separador) {
    if (texto == NULL)
        return NULL;

    struct vector *v = malloc(sizeof(struct vector));
    if (!v)
        return NULL;

    int capacidad = CAPACIDAD_INICIAL;
    v->palabras = malloc(capacidad * sizeof(char *));
    v->cantidad = 0;

    int i = 0, j = 0;
    char buffer[100];

    while (texto[i] != '\0') {
        if (texto[i] != separador) {
            buffer[j++] = texto[i];
        } else {
            buffer[j] = '\0';

            if (v->cantidad >= capacidad) {
                capacidad *= 2;
                char **temp = realloc(v->palabras, capacidad * sizeof(char *));
                if (!temp)
                    return v;
                v->palabras = temp;
            }

            v->palabras[v->cantidad] = malloc((j + 1) * sizeof(char));
            strcpy(v->palabras[v->cantidad], buffer);
            v->cantidad++;
            j = 0;
        }
        i++;
    }

    buffer[j] = '\0';

    if (v->cantidad >= capacidad) {
        capacidad *= 2;
        char **temp = realloc(v->palabras, capacidad * sizeof(char *));
        if (!temp)
            return v;
        v->palabras = temp;
    }

    v->palabras[v->cantidad] = malloc((j + 1) * sizeof(char));
    strcpy(v->palabras[v->cantidad], buffer);
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
