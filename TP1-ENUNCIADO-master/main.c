#include "src/tp1.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("ERROR, falta el nombre del archivo.\n");
		return 1;
	}

	tp1_t *tp = tp1_leer_archivo(argv[1]);
	if (!tp) {
		printf("ERROR, no se pudo leer el archivo.\n");
		return 1;
	}

	printf("Se cargaron %zu pokemones\n", tp1_cantidad(tp));

	tp1_destruir(tp);
	return 0;
}