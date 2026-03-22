#include "split.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 10

struct vector *split(char *texto, char separador) {
    if (texto == NULL) {
        return NULL;
    }

    struct vector *v = malloc(sizeof(struct vector));
    if (!v) {
        return NULL;
    }

    size_t capacidad = CAPACIDAD_INICIAL;
    v->palabras = malloc(capacidad * sizeof(char *));
    if (!v->palabras) {
        free(v);
        return NULL;
    }
    v->cantidad = 0;

    size_t i = 0;
    size_t inicio = 0;

    while (1) {
        if (texto[i] == separador || texto[i] == '\0') {
            size_t largo_palabra = i - inicio;

            if (v->cantidad >= capacidad) {
                capacidad *= 2;
                char **temp = realloc(v->palabras, capacidad * sizeof(char *));
                if (!temp) {
                    return v;
                }
                v->palabras = temp;
            }

            v->palabras[v->cantidad] = malloc(largo_palabra + 1);
            if (v->palabras[v->cantidad]) {
                memcpy(v->palabras[v->cantidad], &texto[inicio], largo_palabra);
                v->palabras[v->cantidad][largo_palabra] = '\0';
                v->cantidad++;
            }

            if (texto[i] == '\0') {
                break;
            }
            inicio = i + 1;
        }
        i++;
    }

    return v;
}

void vector_destruir(struct vector *v) {
    if (!v) {
        return;
    }
    for (size_t i = 0; i < v->cantidad; i++) {
        free(v->palabras[i]);
    }
    free(v->palabras);
    free(v);
}
