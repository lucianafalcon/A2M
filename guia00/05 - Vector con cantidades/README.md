En el vector pasado por parámetro, se encuentra anotado la cantidad de pokemones que cada entrenador posee. Se requiere modificar el vector pasado por parámetro, que poseerá a los entrenadores que tengan más pokemones que el pasado por parámetro. Se devolverá el tope del mismo.

Así, un ejemplo sería

`vector -> [1, 7, 2, 15, 3, 0, 4, 8]`

En donde las posiciones pares (0, 2, 4 y 6) representan el número del entrenador (el entrenador 1, 2, 3 y 4 respectivamente) y las posiciones impares (1, 3, 5 y 7) representan la cantidad de pokemones que el entrenador en la posición a la izquierda posee.

Entonces, el entrenador 1 tiene 7 pokemones; el 2 tiene 15 pokemones; el 3 tiene 0 pokemones; el 4 tiene 8 pokemones.

De esta manera, si la cantidad de pokemones requeridos es más de 7 pokemones , el vector modificado debería ser

```
vector_modificado -> [2, 4]
valor_devuelto -> 2
```

Asumir que el vector no va a tener números negativos y que siempre poseerá una cantidad par de elementos.

