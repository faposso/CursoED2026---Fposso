# Informe técnico del proyecto

## 1. Nombre del proyecto
Sistema de gestión para el Terminal Portuario Turístico de Buenaventura.

## 2. Objetivo general
Diseñar e implementar un programa en lenguaje C que permita gestionar destinos, colas FIFO de pasajeros, empresas responsables y árboles AVL de viajes programados, utilizando estructuras dinámicas y apuntadores.

## 3. Alcance del sistema
El programa permite:
- Registrar destinos dinámicamente.
- Registrar pasajeros en la cola de un destino específico.
- Mostrar los pasajeros registrados por destino.
- Registrar viajes programados en un árbol AVL.
- Buscar viajes por código.
- Mostrar el árbol de viajes.
- Realizar embarque del primer pasajero en espera.
- Consultar la ubicación de un pasajero.
- Mostrar estadísticas básicas del sistema.

## 4. Estructuras utilizadas
### 4.1 Cola FIFO
Cada destino contiene una cola de pasajeros que permite el almacenamiento dinámico de nodos con los siguientes campos:
- número de documento
- tipo de documento
- estado del pasajero
- apuntador al siguiente nodo

### 4.2 Lista enlazada de destinos
Los destinos se almacenan en una lista enlazada dinámica, lo que permite agregar cualquier cantidad de destinos durante la ejecución.

### 4.3 Árbol AVL
Cada destino tiene un árbol AVL para administrar sus viajes programados. La clave principal es el código del viaje. El árbol se balancea automáticamente al insertar un nuevo viaje.

## 5. Archivos del proyecto
- pruena.c: función principal del programa.
- terminal.h: declaración de estructuras y prototipos.
- terminal.c: funciones generales del sistema, menús, estadísticas y manejo de memoria.
- destinos.c: registro y gestión de destinos y pasajeros.
- viajes.c: inserción, búsqueda, recorrido y balanceo AVL.

## 6. Reglas de negocio implementadas
- Se admiten únicamente los tipos de documento: cédula, pasaporte y tarjeta de identidad.
- Se evita registrar un mismo pasajero en más de una cola.
- El embarque se realiza siguiendo el orden de llegada de la cola FIFO.
- Los viajes se organizan por código en un árbol AVL balanceado.

## 7. Compilación
Para compilar en Windows con GCC:
```bash
gcc -Wall -Wextra -std=c99 -o terminal.exe pruena.c terminal.c destinos.c viajes.c
```

## 8. Observaciones
El proyecto está desarrollado con modularización, uso de memoria dinámica y apuntadores, cumpliendo con la estructura solicitada para la entrega.
