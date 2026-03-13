Ahora que vimos la diferencia entre vector de chars y strings, incluyamos la biblioteca de strings y aprovechémosla!

Se reciben tres strings (como avisamos que son strings, se puede asumir que poseen el '\0'). Se pide que el primero se concatene con el segundo, y que se devuelva el resultado de comparar este nuevo string con el tercero. Cuál iría antes en el diccionario? Si el string concatenado aparecería primero o ambos son iguales, se devuelve la letra 'C; . Si el tercer string pasado por parámetro aparecería primero, se devuelve la letra 'S'.

Veamos un ejemplo. Recibo los strings "Algo", "ritmo" y "Programación". Si concateno el primer y segundo string, obtengo "Algoritmo". Comparo "Algoritmo" con "Programación" y obtengo que "Algoritmo" debería ir primero en el diccionario, así que debo devolver la letra 'C'.

Ya incluimos por vos la librería en `solucion.h` ;)

*Ayudita*: buscá qué funciones interesantes hay en la biblioteca `string.h` ;)