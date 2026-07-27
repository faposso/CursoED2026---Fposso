#include "terminal.h"

Destino *inicioDestinos = NULL;
int totalPasajerosRegistrados = 0;
int totalPasajerosEmbarcados = 0;
int totalDestinos = 0;

void inicializarSistema() {
    inicioDestinos = NULL;
    totalPasajerosRegistrados = 0;
    totalPasajerosEmbarcados = 0;
    totalDestinos = 0;
}

void limpiarEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void mostrarMenu() {
    printf("\n===== TERMINAL PORTUARIO TURISTICO =====\n");
    printf("1. Registrar destino\n");
    printf("2. Registrar pasajero\n");
    printf("3. Mostrar pasajeros por destino\n");
    printf("4. Registrar viaje programado\n");
    printf("5. Buscar viaje\n");
    printf("6. Mostrar arbol de viajes\n");
    printf("7. Realizar embarque\n");
    printf("8. Consultar pasajero\n");
    printf("9. Mostrar destinos registrados\n");
    printf("10. Mostrar estadisticas\n");
    printf("0. Salir\n");
    printf("======================================\n");
}

Destino *buscarDestinoPorCodigo(int codigo) {
    Destino *actual = inicioDestinos;
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void agregarDestino(Destino *nuevoDestino) {
    nuevoDestino->siguiente = inicioDestinos;
    inicioDestinos = nuevoDestino;
    totalDestinos++;
}

void mostrarDestino(Destino *destino) {
    if (destino == NULL) {
        return;
    }

    printf("Codigo: %d\n", destino->codigo);
    printf("Nombre: %s\n", destino->nombre);
    printf("Empresa: %s\n", destino->empresa);
    printf("Pasajeros en espera: %d\n", destino->cola.cantidad);
    printf("Viajes registrados: ");
    if (destino->raizViajes == NULL) {
        printf("No hay viajes\n");
    } else {
        printf("Si\n");
    }
    printf("-------------------------------\n");
}

void mostrarTodosDestinos() {
    Destino *actual = inicioDestinos;
    if (actual == NULL) {
        printf("No hay destinos registrados.\n");
        return;
    }

    printf("\nDestinos registrados:\n");
    while (actual != NULL) {
        mostrarDestino(actual);
        actual = actual->siguiente;
    }
}

void liberarSistema() {
    Destino *actual = inicioDestinos;
    while (actual != NULL) {
        Destino *siguiente = actual->siguiente;
        liberarColaPasajeros(&actual->cola);
        liberarArbolViajes(actual->raizViajes);
        free(actual);
        actual = siguiente;
    }

    inicioDestinos = NULL;
    totalPasajerosRegistrados = 0;
    totalPasajerosEmbarcados = 0;
    totalDestinos = 0;
}

void mostrarEstadisticas() {
    Destino *actual = inicioDestinos;
    int totalEspera = 0;
    int totalViajes = 0;
    int totalEmbarcadosPorViaje = 0;
    Destino *destinoMayor = NULL;
    Destino *destinoMenor = NULL;
    int mayorEspera = -1;
    int menorEspera = -1;

    if (actual == NULL) {
        printf("No hay datos para mostrar.\n");
        return;
    }

    while (actual != NULL) {
        totalEspera += actual->cola.cantidad;
        if (mayorEspera == -1 || actual->cola.cantidad > mayorEspera) {
            mayorEspera = actual->cola.cantidad;
            destinoMayor = actual;
        }
        if (menorEspera == -1 || actual->cola.cantidad < menorEspera) {
            menorEspera = actual->cola.cantidad;
            destinoMenor = actual;
        }

        NodoViaje *raiz = actual->raizViajes;
        while (raiz != NULL) {
            totalViajes++;
            totalEmbarcadosPorViaje += raiz->pasajerosEmbarcados;
            raiz = raiz->der;
        }

        actual = actual->siguiente;
    }

    printf("\n==== ESTADISTICAS ====\n");
    printf("Total de destinos: %d\n", totalDestinos);
    printf("Total de pasajeros registrados: %d\n", totalPasajerosRegistrados);
    printf("Total de pasajeros embarcados: %d\n", totalPasajerosEmbarcados);
    if (totalDestinos > 0) {
        printf("Promedio de pasajeros en espera por destino: %.2f\n", (float) totalEspera / totalDestinos);
    } else {
        printf("Promedio de pasajeros en espera por destino: 0.00\n");
    }
    if (totalViajes > 0) {
        printf("Promedio de pasajeros embarcados por viaje: %.2f\n", (float) totalEmbarcadosPorViaje / totalViajes);
    } else {
        printf("Promedio de pasajeros embarcados por viaje: 0.00\n");
    }
    if (destinoMayor != NULL) {
        printf("Destino con mayor espera: %s (%d)\n", destinoMayor->nombre, mayorEspera);
    }
    if (destinoMenor != NULL) {
        printf("Destino con menor espera: %s (%d)\n", destinoMenor->nombre, menorEspera);
    }
}
