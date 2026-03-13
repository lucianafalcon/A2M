#define MAX_NOMBRE_POKEMON 20
#define MAX_VECTOR 10
#include <string.h>

typedef struct pokemon{
    char nombre[MAX_NOMBRE_POKEMON];
    int victorias;
} pokemon_t;


pokemon_t pokemon_con_mas_victorias(pokemon_t pokemones[MAX_VECTOR], int tope_vector);