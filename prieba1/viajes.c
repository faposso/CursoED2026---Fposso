#include "terminal.h"

static int maximo(int a, int b) {
    return a > b ? a : b;
}

static int alturaNodo(NodoViaje *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

static int factorEquilibrio(NodoViaje *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return alturaNodo(nodo->izq) - alturaNodo(nodo->der);
}

static NodoViaje *rotarDerecha(NodoViaje *y) {
    NodoViaje *x = y->izq;
    NodoViaje *t2 = x->der;

    x->der = y;
    y->izq = t2;

    y->altura = maximo(alturaNodo(y->izq), alturaNodo(y->der)) + 1;
    x->altura = maximo(alturaNodo(x->izq), alturaNodo(x->der)) + 1;

    return x;
}

static NodoViaje *rotarIzquierda(NodoViaje *x) {
    NodoViaje *y = x->der;
    NodoViaje *t2 = y->izq;

    y->izq = x;
    x->der = t2;

    x->altura = maximo(alturaNodo(x->izq), alturaNodo(x->der)) + 1;
    y->altura = maximo(alturaNodo(y->izq), alturaNodo(y->der)) + 1;

    return y;
}

static NodoViaje *balancearArbol(NodoViaje *nodo) {
    if (nodo == NULL) {
        return NULL;
    }

    nodo->altura = maximo(alturaNodo(nodo->izq), alturaNodo(nodo->der)) + 1;
    int fe = factorEquilibrio(nodo);

    if (fe > 1) {
        if (factorEquilibrio(nodo->izq) < 0) {
            nodo->izq = rotarIzquierda(nodo->izq);
        }
        return rotarDerecha(nodo);
    }

    if (fe < -1) {
        if (factorEquilibrio(nodo->der) > 0) {
            nodo->der = rotarDerecha(nodo->der);
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoViaje *insertarViajeEnArbol(NodoViaje *raiz, int codigo, int capacidad) {
    if (raiz == NULL) {
        NodoViaje *nuevo = (NodoViaje *) malloc(sizeof(NodoViaje));
        if (nuevo == NULL) {
            printf("No se pudo reservar memoria.\n");
            return NULL;
        }
        nuevo->codigo = codigo;
        nuevo->capacidad = capacidad;
        nuevo->altura = 1;
        nuevo->pasajerosEmbarcados = 0;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        return nuevo;
    }

    if (codigo < raiz->codigo) {
        raiz->izq = insertarViajeEnArbol(raiz->izq, codigo, capacidad);
    } else if (codigo > raiz->codigo) {
        raiz->der = insertarViajeEnArbol(raiz->der, codigo, capacidad);
    } else {
        printf("El codigo del viaje ya existe.\n");
        return raiz;
    }

    return balancearArbol(raiz);
}

NodoViaje *buscarViajeEnArbol(NodoViaje *raiz, int codigo) {
    if (raiz == NULL) {
        return NULL;
    }

    if (codigo == raiz->codigo) {
        return raiz;
    }
    if (codigo < raiz->codigo) {
        return buscarViajeEnArbol(raiz->izq, codigo);
    }
    return buscarViajeEnArbol(raiz->der, codigo);
}

void mostrarViajesEnOrden(NodoViaje *raiz) {
    if (raiz == NULL) {
        return;
    }

    mostrarViajesEnOrden(raiz->izq);
    printf("Codigo: %d | Capacidad: %d | Embarcados: %d\n",
           raiz->codigo, raiz->capacidad, raiz->pasajerosEmbarcados);
    mostrarViajesEnOrden(raiz->der);
}

void liberarArbolViajes(NodoViaje *raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarArbolViajes(raiz->izq);
    liberarArbolViajes(raiz->der);
    free(raiz);
}

void registrarViaje() {
    int codigoDestino;
    int codigoViaje;
    int capacidad;

    printf("\nIngrese codigo del destino: ");
    scanf("%d", &codigoDestino);
    limpiarEntrada();

    Destino *destino = buscarDestinoPorCodigo(codigoDestino);
    if (destino == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    printf("Ingrese codigo del viaje: ");
    scanf("%d", &codigoViaje);
    limpiarEntrada();

    printf("Ingrese capacidad maxima: ");
    scanf("%d", &capacidad);
    limpiarEntrada();

    if (buscarViajeEnArbol(destino->raizViajes, codigoViaje) != NULL) {
        printf("El codigo del viaje ya existe.\n");
        return;
    }

    destino->raizViajes = insertarViajeEnArbol(destino->raizViajes, codigoViaje, capacidad);
    if (destino->raizViajes != NULL) {
        printf("Viaje registrado correctamente.\n");
    }
}

void buscarViaje() {
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

    printf("Ingrese codigo del viaje: ");
    scanf("%d", &codigoViaje);
    limpiarEntrada();

    NodoViaje *viaje = buscarViajeEnArbol(destino->raizViajes, codigoViaje);
    if (viaje == NULL) {
        printf("Viaje no encontrado.\n");
    } else {
        printf("Viaje encontrado. Capacidad: %d | Embarcados: %d\n",
               viaje->capacidad, viaje->pasajerosEmbarcados);
    }
}

void mostrarArbolViajes() {
    int codigoDestino;
    printf("\nIngrese codigo del destino: ");
    scanf("%d", &codigoDestino);
    limpiarEntrada();

    Destino *destino = buscarDestinoPorCodigo(codigoDestino);
    if (destino == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    if (destino->raizViajes == NULL) {
        printf("No hay viajes programados para este destino.\n");
        return;
    }

    printf("\nViajes programados del destino %s:\n", destino->nombre);
    mostrarViajesEnOrden(destino->raizViajes);
}
