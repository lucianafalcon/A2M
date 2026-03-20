#ifndef SPLIT_H
#define SPLIT_H

struct vector {
	unsigned int cantidad;
	char **palabras;
};

/**
 * Divide un texto en palabras utilizando un separador específico.
 * 
 * Por ejemplo, si el texto es "Hola;1;2;3;mundo" y el separador es ';',
 * la función devolverá un vector con las palabras ["Hola", "1", "2", "3", "mundo"].
 */
struct vector *split(char *texto, char separador);

/**
 * Libera la memoria utilizada por el vector de palabras.
 */
void vector_destruir(struct vector *v);

#endif