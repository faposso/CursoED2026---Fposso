#include "terminal.h"

static int documentoValido(int tipo) {
    return tipo == TIPO_CC || tipo == TIPO_PASAPORTE || tipo == TIPO_TI;
}

static int existePasajeroEnSistema(int documento) {
    Destino *actual = inicioDestinos;
    while (actual != NULL) {
        NodoPasajero *aux = actual->cola.frente;
        while (aux != NULL) {
            if (aux->documento == documento) {
                return 1;
            }
            aux = aux->siguiente;
        }
        actual = actual->siguiente;
    }
    return 0;
}

int contarPasajerosEspera(ColaPasajeros *cola) {
    return cola != NULL ? cola->cantidad : 0;
}

int verificarColaVacia(ColaPasajeros *cola) {
    return cola == NULL || cola->cantidad == 0;
}

void encolarPasajero(ColaPasajeros *cola, NodoPasajero *nuevo) {
    if (cola == NULL || nuevo == NULL) {
        return;
    }

    nuevo->siguiente = NULL;
    if (cola->final == NULL) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
    cola->cantidad++;
}

NodoPasajero *desencolarPasajero(ColaPasajeros *cola) {
    if (cola == NULL || cola->frente == NULL) {
        return NULL;
    }

    NodoPasajero *temporal = cola->frente;
    cola->frente = temporal->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
    cola->cantidad--;
    temporal->siguiente = NULL;
    return temporal;
}

NodoPasajero *consultarPrimerPasajero(ColaPasajeros *cola) {
    return cola != NULL ? cola->frente : NULL;
}

void liberarColaPasajeros(ColaPasajeros *cola) {
    if (cola == NULL) {
        return;
    }

    NodoPasajero *actual = cola->frente;
    while (actual != NULL) {
        NodoPasajero *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    cola->frente = NULL;
    cola->final = NULL;
    cola->cantidad = 0;
}

void registrarDestino() {
    Destino *nuevoDestino = (Destino *) malloc(sizeof(Destino));
    if (nuevoDestino == NULL) {
        printf("No se pudo reservar memoria.\n");
        return;
    }

    printf("\nIngrese codigo del destino: ");
    scanf("%d", &nuevoDestino->codigo);
    limpiarEntrada();

    if (buscarDestinoPorCodigo(nuevoDestino->codigo) != NULL) {
        printf("El codigo ya existe.\n");
        free(nuevoDestino);
        return;
    }

    printf("Ingrese nombre del destino: ");
    fgets(nuevoDestino->nombre, MAX_NOMBRE, stdin);
    nuevoDestino->nombre[strcspn(nuevoDestino->nombre, "\n")] = '\0';

    printf("Ingrese nombre de la empresa: ");
    fgets(nuevoDestino->empresa, MAX_NOMBRE, stdin);
    nuevoDestino->empresa[strcspn(nuevoDestino->empresa, "\n")] = '\0';

    nuevoDestino->cola.frente = NULL;
    nuevoDestino->cola.final = NULL;
    nuevoDestino->cola.cantidad = 0;
    nuevoDestino->raizViajes = NULL;
    nuevoDestino->siguiente = NULL;

    agregarDestino(nuevoDestino);
    printf("Destino registrado correctamente.\n");
}

void registrarPasajero() {
    int codigoDestino;
    int documento;
    int tipoDocumento;

    printf("\nIngrese codigo del destino: ");
    scanf("%d", &codigoDestino);
    limpiarEntrada();

    Destino *destino = buscarDestinoPorCodigo(codigoDestino);
    if (destino == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    printf("Ingrese numero de documento: ");
    scanf("%d", &documento);
    limpiarEntrada();

    printf("Seleccione tipo de documento:\n");
    printf("1. Cedula de Ciudadania\n");
    printf("2. Pasaporte\n");
    printf("3. Tarjeta de Identidad\n");
    scanf("%d", &tipoDocumento);
    limpiarEntrada();

    if (!documentoValido(tipoDocumento)) {
        printf("Tipo de documento no permitido.\n");
        return;
    }

    if (existePasajeroEnSistema(documento)) {
        printf("El pasajero ya existe en otra cola.\n");
        return;
    }

    NodoPasajero *nuevoPasajero = (NodoPasajero *) malloc(sizeof(NodoPasajero));
    if (nuevoPasajero == NULL) {
        printf("No se pudo reservar memoria.\n");
        return;
    }

    nuevoPasajero->documento = documento;
    nuevoPasajero->tipoDocumento = (TipoDocumento) tipoDocumento;
    nuevoPasajero->estado = ESTADO_ESPERA;
    nuevoPasajero->siguiente = NULL;

    encolarPasajero(&destino->cola, nuevoPasajero);
    totalPasajerosRegistrados++;
    printf("Pasajero registrado en la fila del destino.\n");
}

void mostrarPasajerosPorDestino() {
    int codigoDestino;
    printf("\nIngrese codigo del destino: ");
    scanf("%d", &codigoDestino);
    limpiarEntrada();

    Destino *destino = buscarDestinoPorCodigo(codigoDestino);
    if (destino == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    printf("\nPasajeros del destino %s:\n", destino->nombre);
    if (verificarColaVacia(&destino->cola)) {
        printf("No hay pasajeros en espera.\n");
        return;
    }

    NodoPasajero *actual = destino->cola.frente;
    while (actual != NULL) {
        printf("Documento: %d | Estado: %s\n", actual->documento,
               actual->estado == ESTADO_ESPERA ? "En espera" : "Embarcado");
        actual = actual->siguiente;
    }
}

void realizarEmbarque() {
    int codigoDestino;
    int codigoViaje;

    printf("\nIngrese codigo del destino: ");
    scanf("%d", &codigoDestino);
    limpiarEntrada();

    Destino *destino = buscarDestinoPorCodigo(codigoDestino);
    if (destino == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    if (verificarColaVacia(&destino->cola)) {
        printf("No hay pasajeros en espera.\n");
        return;
    }

    printf("Ingrese codigo del viaje: ");
    scanf("%d", &codigoViaje);
    limpiarEntrada();

    NodoViaje *viaje = buscarViajeEnArbol(destino->raizViajes, codigoViaje);
    if (viaje == NULL) {
        printf("No existe un viaje programado con ese codigo.\n");
        return;
    }

    NodoPasajero *pasajero = desencolarPasajero(&destino->cola);
    if (pasajero == NULL) {
        printf("No fue posible embarcar.\n");
        return;
    }

    pasajero->estado = ESTADO_EMBARCADO;
    viaje->pasajerosEmbarcados++;
    totalPasajerosEmbarcados++;
    free(pasajero);
    printf("Pasajero embarcado correctamente.\n");
}

void consultarPasajero() {
    int documento;
    printf("\nIngrese numero de documento: ");
    scanf("%d", &documento);
    limpiarEntrada();

    Destino *actual = inicioDestinos;
    while (actual != NULL) {
        NodoPasajero *aux = actual->cola.frente;
        while (aux != NULL) {
            if (aux->documento == documento) {
                printf("Pasajero encontrado en el destino %s.\n", actual->nombre);
                printf("Estado: %s\n", aux->estado == ESTADO_ESPERA ? "En espera" : "Embarcado");
                return;
            }
            aux = aux->siguiente;
        }
        actual = actual->siguiente;
    }

    printf("No se encontro el pasajero.\n");
}