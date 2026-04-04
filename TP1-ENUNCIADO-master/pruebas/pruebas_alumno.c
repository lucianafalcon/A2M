#include "pa2m.h"
#include "../src/tp1.h"
#include <string.h>

/**
 * DISCLAIMER:
 * - Esto es un ejemplo, este código no debe ser parte del archivo definitivo al
 *   momento de la entrega final.
 * - Las funciones que se prueban (ej. sumar, es_par) se deben implementar
 *   en los archivos de código correspondientes (por ejemplo, lista.c), no
 *   dentro de los archivos de pruebas.
 * - En este ejemplo se incluyen funciones mínimas implementadas (sumar(), las
 *   demás son funciones necesarias para pruebas) solo para que el ejemplo
 *   compile y se entienda la estructura de las pruebas.
 * - Para ver algo un poco más completo, revisar el template de ejemplo de
 *   tests.
 */

void pruebas_creacion_y_lectura()
{
	pa2m_nuevo_grupo("Pruebas de Creación y Lectura");

	tp1_t *tp = tp1_leer_archivo("archivo.csv");

	pa2m_afirmar(tp != NULL, "Se pudo leer el archivo 'archivo.csv'");
	pa2m_afirmar(
		tp1_cantidad(tp) == 3,
		"La cantidad de pokemones leídos es 3 (ignora repetidos y basura)");

	tp1_destruir(tp);
}

void pruebas_busqueda()
{
	pa2m_nuevo_grupo("Pruebas de Búsqueda");

	tp1_t *tp = tp1_leer_archivo("archivo.csv");

	struct pokemon *p = tp1_buscar_nombre(tp, "Pikachu");
	pa2m_afirmar(p != NULL, "Se encontró a Pikachu");
	if (p) {
		pa2m_afirmar(p->ataque == 55, "Pikachu tiene ataque 55");
	}

	pa2m_afirmar(tp1_buscar_nombre(tp, "Inexistente") == NULL,
		     "Buscar un pokemon que no existe devuelve NULL");

	tp1_destruir(tp);
}

void pruebas_filtrado()
{
	pa2m_nuevo_grupo("Pruebas de Filtrado");

	tp1_t *tp = tp1_leer_archivo("archivo.csv");
	tp1_t *fuego = tp1_filtrar_tipo(tp, TIPO_FUEG);

	pa2m_afirmar(fuego != NULL, "Se pudo crear el TP filtrado");
	pa2m_afirmar(tp1_cantidad(fuego) == 1,
		     "El filtro de FUEGO tiene 1 pokemon (Charmander)");

	tp1_destruir(fuego);
	tp1_destruir(tp);
}

int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP X ===============");

	pa2m_nuevo_grupo("Pruebas de Suma del TDA X");
	pruebas_creacion_y_lectura();
	pruebas_busqueda();
	pruebas_filtrado();

	return pa2m_mostrar_reporte();
}