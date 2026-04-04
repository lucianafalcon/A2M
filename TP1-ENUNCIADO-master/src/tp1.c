#include "tp1.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct tp1 {
	struct pokemon **pokemon;
	size_t cantidad;
};

/*** AUX ***/

static void consumir_linea(FILE *archivo)
{
	int c;
	while ((c = fgetc(archivo)) != '\n' && c != EOF)
		;
}

static char *leer_campo_din(FILE *archivo)
{
	size_t tam = 0;
	char *buffer = NULL;

	int c = fgetc(archivo);
	if (c == EOF || c == '\n' || c == '\r') {
		if (c != EOF)
			ungetc(c, archivo);
		return NULL;
	}

	while (c != ',' && c != '\n' && c != EOF) {
		if (c != '\r') {
			char *aux = realloc(buffer, tam + 2);
			if (!aux) {
				free(buffer);
				return NULL;
			}
			buffer = aux;
			buffer[tam++] = (char)c;
		}
		c = fgetc(archivo);
	}

	if (c != EOF)
		ungetc(c, archivo);

	if (!buffer) {
		buffer = calloc(1, 1);
		if (!buffer)
			return NULL;
	} else {
		buffer[tam] = '\0';
	}

	int proximo = fgetc(archivo);
	if (proximo != ',')
		ungetc(proximo, archivo);

	return buffer;
}

static enum tipo_pokemon conversor_texto_enum(char *texto)
{
	if (!texto)
		return (enum tipo_pokemon) - 1;

	if (strcasecmp(texto, "ELEC") == 0)
		return TIPO_ELEC;
	if (strcasecmp(texto, "FUEG") == 0)
		return TIPO_FUEG;
	if (strcasecmp(texto, "PLAN") == 0)
		return TIPO_PLAN;
	if (strcasecmp(texto, "AGUA") == 0)
		return TIPO_AGUA;
	if (strcasecmp(texto, "NORM") == 0)
		return TIPO_NORM;
	if (strcasecmp(texto, "FANT") == 0)
		return TIPO_FANT;
	if (strcasecmp(texto, "PSI") == 0)
		return TIPO_PSI;
	if (strcasecmp(texto, "LUCH") == 0)
		return TIPO_LUCH;

	return (enum tipo_pokemon) - 1;
}

static const char *tipo_a_texto(enum tipo_pokemon tipo)
{
	switch (tipo) {
	case TIPO_ELEC:
		return "ELEC";
	case TIPO_FUEG:
		return "FUEG";
	case TIPO_PLAN:
		return "PLAN";
	case TIPO_AGUA:
		return "AGUA";
	case TIPO_NORM:
		return "NORM";
	case TIPO_FANT:
		return "FANT";
	case TIPO_PSI:
		return "PSI";
	case TIPO_LUCH:
		return "LUCH";
	default:
		return "NORM";
	}
}

static void ordenar(tp1_t *tp)
{
	for (size_t i = 0; i + 1 < tp->cantidad; i++) {
		for (size_t j = 0; j + 1 < tp->cantidad - i; j++) {
			if (strcasecmp(tp->pokemon[j]->nombre,
				       tp->pokemon[j + 1]->nombre) > 0) {
				struct pokemon *aux = tp->pokemon[j];
				tp->pokemon[j] = tp->pokemon[j + 1];
				tp->pokemon[j + 1] = aux;
			}
		}
	}
}

/*** FUNCIONES ***/

tp1_t *tp1_leer_archivo(const char *nombre_archivo)
{
	if (!nombre_archivo)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (!archivo)
		return NULL;

	tp1_t *tp = malloc(sizeof(tp1_t));
	if (!tp) {
		fclose(archivo);
		return NULL;
	}
	tp->pokemon = NULL;
	tp->cantidad = 0;

	while (true) {
		char *nombre = leer_campo_din(archivo);
		if (!nombre) {
			int c = fgetc(archivo);
			if (c == EOF)
				break;
			consumir_linea(archivo);
			continue;
		}

		char *tipo_s = leer_campo_din(archivo);
		char *atq_s = leer_campo_din(archivo);
		char *def_s = leer_campo_din(archivo);
		char *vel_s = leer_campo_din(archivo);

		bool basura_extra = false;
		int c = fgetc(archivo);
		while (c != '\n' && c != EOF) {
			if (c != ' ' && c != '\t' && c != '\r')
				basura_extra = true;
			c = fgetc(archivo);
		}

		if (!tipo_s || !atq_s || !def_s || !vel_s || basura_extra) {
			free(nombre);
			free(tipo_s);
			free(atq_s);
			free(def_s);
			free(vel_s);
			continue;
		}

		char *e1, *e2, *e3;
		long a = strtol(atq_s, &e1, 10);
		long d = strtol(def_s, &e2, 10);
		long v = strtol(vel_s, &e3, 10);
		enum tipo_pokemon t = conversor_texto_enum(tipo_s);

		if (*e1 != '\0' || *e2 != '\0' || *e3 != '\0' || (int)t == -1) {
			free(nombre);
			free(tipo_s);
			free(atq_s);
			free(def_s);
			free(vel_s);
			continue;
		}

		free(atq_s);
		free(def_s);
		free(vel_s);

		bool repetido = false;
		for (size_t i = 0; i < tp->cantidad; i++) {
			if (strcasecmp(tp->pokemon[i]->nombre, nombre) == 0) {
				repetido = true;
				break;
			}
		}

		if (repetido) {
			free(nombre);
			free(tipo_s);
			continue;
		}

		struct pokemon *p = malloc(sizeof(struct pokemon));
		struct pokemon **aux =
			realloc(tp->pokemon,
				sizeof(struct pokemon *) * (tp->cantidad + 1));

		if (!p || !aux) {
			free(p);
			free(nombre);
			free(tipo_s);
			continue;
		}

		p->nombre = nombre;
		p->tipo = t;
		p->ataque = (int)a;
		p->defensa = (int)d;
		p->velocidad = (int)v;
		tp->pokemon = aux;
		tp->pokemon[tp->cantidad++] = p;
		free(tipo_s);
	}

	if (tp->cantidad > 0)
		ordenar(tp);
	fclose(archivo);
	return tp;
}

size_t tp1_cantidad(tp1_t *tp)
{
	return tp ? tp->cantidad : 0;
}

tp1_t *tp1_guardar_archivo(tp1_t *tp, const char *nombre)
{
	if (!tp || !nombre)
		return NULL;
	FILE *archivo = fopen(nombre, "w");
	if (!archivo)
		return NULL;
	for (size_t i = 0; i < tp->cantidad; i++) {
		struct pokemon *p = tp->pokemon[i];
		fprintf(archivo, "%s,%s,%d,%d,%d\n", p->nombre,
			tipo_a_texto(p->tipo), p->ataque, p->defensa,
			p->velocidad);
	}
	fclose(archivo);
	return tp;
}

tp1_t *tp1_filtrar_tipo(tp1_t *tp, enum tipo_pokemon tipo)
{
	if (!tp)
		return NULL;
	tp1_t *nuevo = malloc(sizeof(tp1_t));
	if (!nuevo)
		return NULL;
	nuevo->pokemon = NULL;
	nuevo->cantidad = 0;

	for (size_t i = 0; i < tp->cantidad; i++) {
		if (tp->pokemon[i]->tipo == tipo) {
			struct pokemon *orig = tp->pokemon[i];
			struct pokemon *p = malloc(sizeof(struct pokemon));
			if (!p) {
				tp1_destruir(nuevo);
				return NULL;
			}
			p->nombre = malloc(strlen(orig->nombre) + 1);
			if (!p->nombre) {
				free(p);
				tp1_destruir(nuevo);
				return NULL;
			}
			strcpy(p->nombre, orig->nombre);
			p->tipo = orig->tipo;
			p->ataque = orig->ataque;
			p->defensa = orig->defensa;
			p->velocidad = orig->velocidad;

			struct pokemon **aux = realloc(
				nuevo->pokemon, sizeof(struct pokemon *) *
							(nuevo->cantidad + 1));
			if (!aux) {
				free(p->nombre);
				free(p);
				tp1_destruir(nuevo);
				return NULL;
			}
			nuevo->pokemon = aux;
			nuevo->pokemon[nuevo->cantidad++] = p;
		}
	}
	return nuevo;
}

struct pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre)
{
	if (!tp || !nombre)
		return NULL;
	for (size_t i = 0; i < tp->cantidad; i++) {
		if (strcasecmp(tp->pokemon[i]->nombre, nombre) == 0)
			return tp->pokemon[i];
	}
	return NULL;
}

struct pokemon *tp1_buscar_orden(tp1_t *tp, int n)
{
	if (!tp || n < 0 || (size_t)n >= tp->cantidad)
		return NULL;
	return tp->pokemon[n];
}

size_t tp1_con_cada_pokemon(tp1_t *tp, bool (*f)(struct pokemon *, void *),
			    void *extra)
{
	if (!tp || !f)
		return 0;
	size_t count = 0;
	for (size_t i = 0; i < tp->cantidad; i++) {
		count++;
		if (!f(tp->pokemon[i], extra))
			break;
	}
	return count;
}

void tp1_destruir(tp1_t *tp)
{
	if (!tp)
		return;
	for (size_t i = 0; i < tp->cantidad; i++) {
		free(tp->pokemon[i]->nombre);
		free(tp->pokemon[i]);
	}
	free(tp->pokemon);
	free(tp);
}