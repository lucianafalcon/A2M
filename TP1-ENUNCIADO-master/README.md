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

El programa funciona como un sistema de gestión y consulta de una base de datos de Pokémon (Pokédex), cuyos datos son cargados desde archivos de texto en formato CSV.

Su objetivo principal es leer y procesar un archivo de entrada, validar la información contenida en cada registro y almacenar los datos en estructuras dinámicas en memoria. A partir de estos datos, el sistema permite al usuario realizar distintas operaciones, como búsquedas específicas (por nombre, tipo) y visualizaciones ordenadas de la colección.

Además, el programa contempla el manejo de errores en la lectura del archivo, validando formatos incorrectos o datos inválidos, lo que garantiza la integridad de la información almacenada.

Proceso de Carga y Validación     
Al iniciar, el programa lee el archivo línea por línea. Cada registro es validado para asegurar que contiene todos los campos necesarios (nombre, tipo y tres tipos numéricos). Si una línea está corrupta o le faltan datos, el programa la ignora y continúa con la siguiente, para no impedir la carga del resto de la Pokedex.   
Respecto a los duplicados, el sistema prioriza la primera aparición: si se encuentra un Pokémon cuyo nombre (sin distinguir mayúsculas de minúsculas) ya existe en la memoria, el nuevo registro se descarta.

Gestión de Memoria y Ordenamiento   
A medida que se leen registros válidos, el sistema expande su capacidad de almacenamiento de forma dinámica. Una vez finalizada la lectura, los datos se ordenan alfabéticamente por nombre de manera automática. Esto permite que cualquier funcionalidad de "mostrar" parta de una base ya organizada.   

Decisiones de Funcionamiento      
Para los casos donde el enunciado no era explícito, se implementaron las siguientes decisiones:   
- Archivos Vacíos: Si el archivo existe pero no tiene registros válidos, el programa informa que la Pokedex está vacía en lugar de finalizar con error.   
- Búsquedas Fallidas: Al buscar un Pokémon que no existe, el programa devuelve un mensaje descriptivo al usuario.      
- Tratamiento de Espacios: Los nombres de los Pokémon pueden contener espacios (por ej "Mr. Mime"), procesándolos como un único campo de texto hasta encontrar la coma separadora.   
- Tipos Desconocidos: Si un Pokémon tiene un código de tipo que no está en la lista oficial, esa línea se considera inválida y se saltea.   

## 3. Estructura

Para implementar la estructura decidí hacerlo con un campo `struct tp1` , además tiene un puntero de entrada a toda la información, y eso permite gestionar los datos de manera eficiente. Ademas se optó por un vector dinámico de punteros para cumplir con la restricción de no presuponer tamaños máximos.

En esta arquitectura, el administrador contiene un puntero doble `struct pokemon **` que apunta a un bloque de memoria donde se almacenan las direcciones de cada Pokémon, el cual, a su vez, es una estructura independiente alojada en el Heap.

Esta decisión de diseño aporta dos ventajas críticas:

* Eficiencia en el realloc: Al redimensionar la estructura (cuando el vector crece), solo movemos punteros (8 bytes cada uno), evitando el costo computacional de copiar estructuras completas con múltiples campos.

* Optimización de ordenamiento: Durante el ordenamiento alfabético, el intercambio de posiciones se realiza sobre los punteros en el vector, manteniendo los datos originales del Pokemon estáticos en su posición del Heap.

### 3.1. Diagrama de memoria

<div align="center">
  <img src="https://github.com/user-attachments/assets/e2be0417-1e61-425d-b7ac-646660b734f6" alt="Diagrama de memoria TP1" width="80%">
  <p><i>Figura 3.1: Diagrama de memoria de la estructura tp1, vector de punteros y nodos pokemon.</i></p>
</div>

En el diagrama de la figura 3.1 se representa la distribución de los elementos: el puntero inicial se encuentra en el Stack, mientras que el administrador tp1, el vector de punteros y las estructuras pokemon individuales residen en el Heap. Se destaca que cada nombre de Pokémon también es un puntero a una cadena de caracteres dinámica, permitiendo soportar nombres de cualquier longitud.


### 3.2. Análisis de complejidades 

| Función | Complejidad |                  Justificación                   |
| :-----: | :---------: | :----------------------------------------------: |
| `tp1_leer_archivo(const char *nombre_archivo)`  |  $O(n^2)$   | Por cada uno de los $n$ registros del archivo, se realiza una búsqueda de duplicados $O(n)$. Además, al finalizar la carga, se aplica un ordenamiento (Bubble Sort) cuya complejidad en el peor caso es cuadrática. |
`*tp1_guardar_archivo(tp1_t *tp, const char *nombre)`  |  $O(n)$   | Recorre el vector una sola vez escribiendo los datos de cada Pokémon en el archivo de salida. |
| `*tp1_filtrar_tipo(tp1_t *tp, enum tipo_pokemon tipo)`  |  $O(n^2)$   | Recorre los $n$ elementos ($O(n)$) y, por cada coincidencia, inserta en un nuevo TP que vuelve a ordenar al final $O(n^2)$. |
| `pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre)`  |   $O(n)$    | Tiene como parámetro el puntero al TP y el nombre a buscar. Realiza un recorrido sobre el vector de punteros a Pokémon comparando cada nombre con strcasecmp hasta encontrarlo o llegar al final. |
| `pokemon *tp1_buscar_orden(tp1_t *tp, int n)`  |  $O(1)$   | Al tener los datos en un vector y estar ya ordenados, el acceso por índice es directo y constante. |
| ` tp1_con_cada_pokemon(tp1_t *tp, bool (*f)(struct pokemon *, void *)`  |   $O(n)$    | Tiene como parámetro el puntero al TP y una función de callback. Recorre el vector de punteros a Pokémon uno por uno (desde el índice 0 hasta $n-1$) invocando la función para cada elemento, asegurando un único paso por la estructura. |
| `tp1_destruir(tp1_t *tp)`  |  $O(n)$   | Debe recorrer el vector para liberar la memoria de cada Pokémon individualmente y finalmente liberar el vector y la estructura principal.  |

Funciones auxiliares: 

`void consumir_linea(FILE *archivo)`,  `char *leer_campo_din(FILE *archivo)` y `enum tipo_pokemon conversor_texto_enum(char *texto)` tienen una complejidad de $O(L)$, donde $L$ es la longitud de la línea o palabra procesada.

`void ordenar(tp1_t *tp)`  es $O(n^2)$ , implementa el algoritmo de Bubble Sort, el cual requiere dos bucles anidados para comparar e intercambiar los punteros del vector en el peor caso. 

`const char *tipo_a_texto(enum tipo_pokemon tipo)` es $O(1)$, realiza un acceso directo (usando un switch o un vector estático) basado en el valor del enum. No requiere comparaciones de strings.



## 4. Decisiones de diseño y/o complejidades de implementación

Gestión de la lectura y robustez   
Una de las mayores complejidades fue la implementación de tp1_leer_archivo. Para cumplir con la restricción de no presuponer longitudes máximas, se diseñó la función auxiliar `leer_campo_din`. Esta función utiliza un buffer dinámico que crece a medida que se leen caracteres, permitiendo procesar nombres o tipos de cualquier extensión sin desbordamientos de memoria. Además, se implementó una política de "barrido de línea" ante errores: si un campo numérico no puede ser convertido o si el formato de la línea es inválido, el programa utiliza una función `consumir_linea` para descartar el resto del registro actual y posicionar el puntero del archivo al inicio de la siguiente línea, evitando así que un error puntual corrompa toda la carga.   

Estrategia de ordenamiento e intercambios   
Se decidió implementar el algoritmo de Bubble Sort operando directamente sobre el vector de punteros. La decisión de diseño de usar un vector de punteros (en lugar de un vector de estructuras) fue crítica ya que al detectar que dos elementos deben ser intercambiados, el programa solo mueve dos punteros (direcciones de memoria), lo cual es una operación de costo constante y mínimo, independientemente del tamaño de la estructura pokemon.

Tratamiento de Duplicados   
Para cumplir con el requisito de conservar solo la primera aparición de un Pokemon, se optó por realizar una búsqueda lineal ($O(n)$) antes de cada inserción. Si bien esto eleva la complejidad de la carga a $O(n^2)$, garantiza la indiscriminación de mayúsculas/minúsculas mediante strcasecmp.

Implementación del Main y Modularización   
En el main.c, se decidió separar la lógica de parseo de argumentos de la lógica de ejecución. Se implementaron funciones de ayuda para transformar los tipos de Pokémon de texto a enum y viceversa, centralizando estas conversiones para facilitar el mantenimiento del código y evitar la repetición de comparaciones de strings a lo largo del programa.


## 5. Respuestas a las preguntas teóricas

### 5.1. Explicar la elección de la estructura para implementar la funcionalida pedida. Justifique el uso de cada uno de los campos de la estructura.

Para este trabajo se utilizó una estructura tp1 que contiene un vector dinámico de punteros a struct pokemon y un contador de cantidad.

Vector de punteros (struct pokemon **pokemon): Se eligió esta estructura porque permite manejar una cantidad indeterminada de pokemones sin conocer de antemano el tamaño del archivo, cumpliendo con la restricción de no presuponer longitudes máximas. Almacenar punteros en lugar de estructuras completas facilita el ordenamiento, ya que solo se intercambian direcciones de memoria.

Cantidad (size_t cantidad): Es fundamental para conocer el tamaño actual del vector, permitiendo iterar sobre él y realizar realocaciones de memoria precisas con realloc.

### 5.2 Dar una definición de complejidad computacional y explique cómo se calcula.   

La complejidad computacional es una medida que permite estimar cuántos recursos (tiempo o memoria) consume un algoritmo en función del tamaño de la entrada ($n$).  
 
<div align="center" style="background-color: white; padding: 10px;">
    <img width="540" height="540" alt="New Template" src="https://github.com/user-attachments/assets/f37cae2e-da12-4a45-a7be-fd69b631d3f0" />
    <p><i>Figura 5.2: Diagrama Big O.</i></p>
</div>

Se expresa generalmente con notación Big-O, como se muestra en la figura 5.2.

Cómo se calcula:  
* Se identifican las operaciones dominantes (como comparaciones o asignaciones dentro de bucles).   
* Se analiza cuántas veces se ejecutan en función de 𝑛.     
* Se descartan constantes y términos menores.   

### 5.3 Explicar con diagramas cómo quedan dispuestas las estructuras y elementos en memoria.
Detalles y representación gráfica en la Sección 3.1 Diagrama de memoria.

### 5.4 Justificar la complejidad computacional temporal de cada una de las funciones que se piden implementar.

Basado en el análisis de la sección 3.2, la justificación técnica es la siguiente:

* tp1_leer_archivo $O(n^2)$: Por cada uno de los $n$ registros leídos del archivo, se realiza una búsqueda lineal para evitar duplicados ($O(n)$). Finalmente, se ejecuta un ordenamiento de burbuja que, en el peor caso, también es cuadrático.   
* tp1_buscar_nombre $O(n)$: Al no estar el vector indexado por nombre de forma asociativa, se debe realizar un recorrido secuencial comparando strings hasta hallar la coincidencia.   
* tp1_buscar_orden $O(1)$: Al utilizar un vector dinámico, el acceso a una posición específica mediante un índice es una operación de tiempo constante.   
* tp1_con_cada_pokemon $O(n)$: La función recorre el vector de principio a fin una sola vez, invocando el callback para cada elemento.   
* tp1_filtrar_tipo $O(n^2)$: Requiere un recorrido completo del vector original ($O(n)$) y, dependiendo de la implementación del ordenamiento en la nueva estructura filtrada, puede alcanzar una complejidad cuadrática.   
* tp1_destruir $O(n)$: Se debe iterar sobre el vector para liberar la memoria de cada Pokémon individualmente antes de liberar el vector y la estructura principal.   

### 5.5 Explique qué dificultades tuvo para implementar las funcionalidades pedidas en el main (si tuvo alguna) y explique si alguna de estas dificultades se podría haber evitado modificando la definición del .h

La principal dificultad radicó en la gestión de los argumentos de línea de comandos (argc y argv) para acoplar las entradas del usuario con las funciones del .h, especialmente en la operación de filtrado y muestra por pantalla.

Dificultades específicas:   
Diferenciación de comandos: El main debe validar si el usuario pidió buscar o mostrar, y en el caso de mostrar, si es por nombre o por tipo.

Falta de un iterador interno con criterio: Si el .h hubiera incluido una función de ordenamiento genérica que aceptara un puntero a función (comparador), se podría haber evitado duplicar lógica de ordenamiento en el main o en funciones privadas para cumplir con el requerimiento de "mostrar por tipo".

Modificación sugerida al .h:   
Si la estructura tp1 incluyera un campo para definir el criterio de ordenamiento actual, o si la función tp1_con_cada_pokemon permitiera especificar un rango o un orden, el main sería mucho más simple y se limitaría a invocar estas funciones sin necesidad de lógica adicional de control.

