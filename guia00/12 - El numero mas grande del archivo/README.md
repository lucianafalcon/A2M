Ya estamos a punto de terminar el repaso de C, lo único que nos queda es cómo interactuar con archivos. Dado el nombre del archivo, se pide que se lean los números almacenados en él y se devuelva el más grande.

El archivo tiene la siguiente estructura `un_numero;otro_numero;y_otro_numero;\n`; el caracter `\n` es un salto de línea. Entonces, los números almacenados en .txt están separados por `;` y no hay espacios entre ellos. Cuando se encuentra con un `\n` es porque ya no hay más elementos. No se sabe de antemano cuántos números hay en el archivo. Se puede asumir que el archivo tendrá como mínimo un elemento.

No te preocupes por el tipo de dato `FILE*`, lo único que tenés que saber es que para usar las funciones de lectura de archivos, tenés que recibir ese tipo de dato.


Si no te acordás las funciones de archivo, las principales son las siguientes:

- fopen, para abrir el archivo
- fclose, para cerrar el archivo (imprescindible si se abre un archivo)
- fscanf, para leer de un archivo según un formato determinado
- fprintf, para escribir en un archivo

En este ejercicio, el archivo ya viene abierto. No te preocupes por cerrarlo, nosotros lo hacemos detrás de cámaras.

#### Un poquito de ayuda

Tenemos que
- el archivo tiene la estructura mencionada más arriba
- la función `fscanf` devuelve la cantidad de elementos que leyó
- no sabemos cuántos elementos hay en el archivo
- cuando necesitamos iterar hasta que cierta condición se deje de cumplir, lo mejor es usar un `while`



Unamos todos estos puntos. Para leer el archivo, podría usar esa estructura iterativa... pero, cuál sería la condición de corte? Sabiendo que la función `fscanf` devuelve la cantidad de elementos que leyó, qué pasa si lee menos de las esperadas? 

