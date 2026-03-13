#include <stdio.h>
#include <string.h>
#define MAX_NOMBRE 30

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int b_ganadas;
    int b_perdidas;
    int b_empatadas;
} pokemon_t;

pokemon_t pokemon_con_mas_batallas(FILE* archivo);