<div align="right">
    <img width="32px" src="img/algo2.svg">
</div>

# TP

## Información del estudiante

- Luciana Falcon
- 107316
- lfalcon@fi.uba.ar

---

## Índice

- [1. Instrucciones](#1-Instrucciones)
  - [1.1. Compilar el proyecto](#11-Compilar-el-proyecto)
  - [1.2. Ejecutar las pruebas](#12-Ejecutar-las-pruebas)
  - [1.3. Ejecutar el programa con Valgrind](#13-Ejecutar-el-programa-con-Valgrind)
- [2. Funcionamiento](#2-Funcionamiento)
- [3. Estructura](#3-Estructura)
  - [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  - [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
- [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
- [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)

## 1. Instrucciones

> [!TIP]
> Se recomienda usar un Makefile y colocar en esta sección los comandos Make.

### 1.1. Compilar el proyecto

```bash
gcc src/tp1.c main.c -o tp1.out
```

### 1.2. Ejecutar las pruebas

```bash
gcc pruebas/pruebas_alumno.c -o pruebas.out
```

### 1.3. Ejecutar el programa con Valgrind

```bash
valgrind --leak-check=full ./pruebas.out
```

## 2. Funcionamiento

Explicar **qué** hace el TP implementado, aclarando todas las decisiones de funcionamiento que no estaban definidas por el enunciado.

> [!IMPORTANT]
> Es muy importante entender la _diferencia entre qué y cómo_. En esta sección **NO** se busca una explicación de cómo implementaste el programa, qué funciones usaste, en qué línea, etc.; se busca una explicación de **qué** es lo que hace el programa en líneas generales.

Se debe incluir todos los diagramas que sean necesarios para explicar el funcionamiento del programa. Las estructuras deberán ser explicadas con diagramas de memoria. Los diagramas pedidos en el enunciado pueden ser colocados en esta sección, pero recordá indicarlo en la sección de respuestas.

> [!WARNING]
> Es importante usar diagramas para explicar los conceptos de forma clara, pero el exceso será negativo. Los diagramas deben tener un fin explicativo y, por lo general, sirven para reemplazar uno o múltiples párrafos de explicación.

## 2. Funcionamiento (EJEMPLO)

El programa recibe 7 números del usuario y una vez obtenidos todos los muestra en pantalla. Para esto define un vector estático de 7 elementos y llena el mismo con los datos que inserta el usuario; cuando termina de insertar todos los números procede a imprimirlos en pantalla.

<div align="center">
  <img src="img/diagrama_flujo_programa.svg" width="70%">
  <p>Diagrama de flujo del programa explicado con más detalle.</p>
</div>

Cuando el vector llega a su máximo el programa procede a escalarlo con un factor de crecimiento..., es decir, si el vector tenía....

## 3. Estructura

Para implementar la estructura decidí hacerlo con un campo ..., además tiene un puntero que... y eso permite que....

Para implementar la estructura decidí hacerlo con un campo `struct tp1` , además tiene un puntero de entrada a toda la información, y eso permite gestionar los datos de manera eficiente. Ademas se optó por un vector dinámico de punteros para cumplir con la restricción de no presuponer tamaños máximos.

En esta arquitectura, el administrador contiene un puntero doble `struct pokemon **` que apunta a un bloque de memoria donde se almacenan las direcciones de cada Pokémon. Cada Pokémon, a su vez, es una estructura independiente alojada en el Heap.

Esta decisión de diseño aporta dos ventajas críticas:

* Eficiencia en el realloc: Al redimensionar la estructura (cuando el vector crece), solo movemos punteros (8 bytes cada uno), evitando el costo computacional de copiar estructuras completas con múltiples campos.

* Optimización de ordenamiento: Durante el ordenamiento alfabético, el intercambio de posiciones se realiza sobre los punteros en el vector, manteniendo los datos originales del Pokémon estáticos en su posición del Heap.

### 3.1. Diagrama de memoria

<div align="center">
  <img src="img/diagrama_memoria__1.svg" width="70%">
  <p>Figura 3.1 Diagrama de memoria de la estructura.</p>
</div>

En el diagrama de la figura 3.1 se representa la distribución de los elementos: el puntero inicial se encuentra en el Stack, mientras que el administrador tp1, el vector de punteros y las estructuras pokemon individuales residen en el Heap. Se destaca que cada nombre de Pokémon también es un puntero a una cadena de caracteres dinámica, permitiendo soportar nombres de cualquier longitud.


### 3.2. Análisis de complejidades 

| Función | Complejidad |                  Justificación                   |
| :-----: | :---------: | :----------------------------------------------: |
| `tp1_leer_archivo(const char *nombre_archivo)`  |  $O(n^2)$   | Por cada uno de los $n$ registros del archivo, se realiza una búsqueda de duplicados ($O(n)$). Además, al finalizar la carga, se aplica un ordenamiento (Bubble Sort) cuya complejidad en el peor caso es cuadrática. |
`*tp1_guardar_archivo(tp1_t *tp, const char *nombre)`  |  $O(n)$   | Recorre el vector una sola vez escribiendo los datos de cada Pokémon en el archivo de salida. |
| `*tp1_filtrar_tipo(tp1_t *tp, enum tipo_pokemon tipo)`  |  $O(n^2)$   | Recorre los $n$ elementos ($O(n)$) y, por cada coincidencia, inserta en un nuevo TP que vuelve a ordenar al final ($O(k^2)$ siendo $k \leq n$). |
| `pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre)`  |   $O(n)$    | Tiene como parámetro el puntero al TP y el nombre a buscar. Realiza un recorrido sobre el vector de punteros a Pokémon comparando cada nombre con strcasecmp hasta encontrarlo o llegar al final. |
| `pokemon *tp1_buscar_orden(tp1_t *tp, int n)`  |  $O(1)$   | Al tener los datos en un vector y estar ya ordenados, el acceso por índice es directo y constante. |
| ` tp1_con_cada_pokemon(tp1_t *tp, bool (*f)(struct pokemon *, void *)`  |   $O(n)$    | Tiene como parámetro el puntero al TP y una función de callback. Recorre el vector de punteros a Pokémon uno por uno (desde el índice 0 hasta $n-1$) invocando la función para cada elemento, asegurando un único paso por la estructura. |
| `tp1_destruir(tp1_t *tp)`  |  $O(n)$   | Debe recorrer el vector para liberar la memoria de cada Pokémon individualmente y finalmente liberar el vector y la estructura principal.  |

Funciones auxiliares: 

`void consumir_linea(FILE *archivo)`,  `char *leer_campo_din(FILE *archivo)` y `enum tipo_pokemon conversor_texto_enum(char *texto)` tienen una complejidad de $O(L)$, donde $L$ es la longitud de la línea o palabra procesada.

`void ordenar(tp1_t *tp)`  es $O(n^2)$ , implementa el algoritmo de Bubble Sort, el cual requiere dos bucles anidados para comparar e intercambiar los punteros del vector en el peor caso. 

`const char *tipo_a_texto(enum tipo_pokemon tipo)` es $O(1)$, realiza un acceso directo (usando un switch o un vector estático) basado en el valor del enum. No requiere comparaciones de strings.



## 4. Decisiones de diseño y/o complejidades de implementación

Explicar las decisiones de diseño y/o las complejidades de implementación que hubo durante la resolución del TP.

## 4. Decisiones de diseño y/o complejidades de implementación (EJEMPLO)

La mayor complejidad en el TP se encuentra en la función `foo` que requiere hacer...; es por esto que decidí.... Además, decidí que el programa haga... para mejorar la implementación.


## 5. Respuestas a las preguntas teóricas

### 5.1. Explicar la elección de la estructura para implementar la funcionalida pedida. Justifique el uso de cada uno de los campos de la estructura.

### 5.2 Dar una definición de complejidad computacional y explique cómo se calcula.

### 5.3 Explicar con diagramas cómo quedan dispuestas las estructuras y elementos en memoria.

### 5.4 Justificar la complejidad computacional temporal de cada una de las funciones que se piden implementar.

### 5.5 Explique qué dificultades tuvo para implementar las funcionalidades pedidas en el main (si tuvo alguna) y explique si alguna de estas dificultades se podría haber evitado modificando la definición del .h


