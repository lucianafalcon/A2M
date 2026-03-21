#include "split.h"
#include <stdlib.h>
#include <string.h>

struct vector *split(char *texto, char separador)
{
    int i=0,j=0;
    char vector_auxiliar[100];

    struct vector *v = malloc(sizeof(struct vector));
    v->palabras = malloc(10 * sizeof(char*)); 
    v->cantidad = 0;

    while(texto[i] != '\0'){
        if(texto[i] != separador){
            vector_auxiliar[j] = texto[i]; 
            j++;
        }else{
            if(j>0){
                vector_auxiliar[j] = '\0';
                v->palabras[v->cantidad] = malloc((j + 1) * sizeof(char));  
                strcpy(v->palabras[v->cantidad], vector_auxiliar);  
                v->cantidad++; 
                j = 0;  
            }
        }
        i++;
    }
	return v;
}

void vector_destruir(struct vector *v)
{
    for (int i = 0; i < v->cantidad; i++) {
        free(v->palabras[i]);
    }
    free(v->palabras);

    free(v);    
}
