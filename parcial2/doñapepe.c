#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Definición de estructuras y constantes
#define MAX_NOMBRE 30
// Estructura para representar un cliente
typedef struct
{
    char nombre[MAX_NOMBRE];
    char sabor[MAX_NOMBRE];
    float litros;
    float total;
} Cliente;
// Estructura para representar un recipiente
typedef struct
{
    char sabor[MAX_NOMBRE];
    float litros;
} Recipiente;

typedef struct NodoCliente
{
    Cliente datos;
    struct NodoCliente *siguiente;
} NodoCliente;

NodoCliente *cabeza = NULL;
NodoCliente *final = NULL;

float totalLitrosSabor(const char sabor[]);
void buscarRecipiente(const char sabor[], float litrosSolicitados);


// Agrega un nuevo cliente a la cola
void encolar()
{
    // Crear un nuevo nodo
    NodoCliente *nuevo = (NodoCliente *)malloc(sizeof(NodoCliente));

    // Verificar si se pudo reservar memoria
    if (nuevo == NULL)
    {
        printf("No hay memoria disponible.\n");
        return;
    }

    // Pedir los datos del cliente
    printf("Nombre del cliente: ");
    scanf(" %[^\n]", nuevo->datos.nombre);

    printf("Sabor: ");
    scanf(" %[^\n]", nuevo->datos.sabor);

    printf("Cantidad de litros: ");
    scanf("%f", &nuevo->datos.litros);

    // Calcular el total
    nuevo->datos.total = nuevo->datos.litros * 8000;

    // Como es el último nodo, no apunta a nadie
    nuevo->siguiente = NULL;

    // Si la cola está vacía
    if (cabeza == NULL)
    {
        cabeza = nuevo;
        final = nuevo;
    }
    else
    {
        // Enlazar el nuevo nodo al final
        final->siguiente = nuevo;

        // Actualizar el último nodo
        final = nuevo;
    }

    printf("Cliente registrado correctamente.\n");
}


// Atiende al primer cliente de la cola
void desencolar()
{
    // Verificar si la cola está vacía
    if (cabeza == NULL)
    {
        printf("No hay clientes en espera.\n");
        return;
    }

    NodoCliente *aux = cabeza;

    printf("\n--- ATENDIENDO CLIENTE ---\n");

    float litrosDisponibles = totalLitrosSabor(aux->datos.sabor);

    if (litrosDisponibles == 0)
    {
        printf("No hay ese sabor disponible.\n");
        return;
    }

    if (litrosDisponibles < aux->datos.litros)
    {
        printf("No hay suficientes litros de ese sabor.\n");
        return;
    }

    buscarRecipiente(aux->datos.sabor, aux->datos.litros);

    printf("Nombre: %s\n", aux->datos.nombre);
    printf("Sabor: %s\n", aux->datos.sabor);
    printf("Cantidad: %.2f litros\n", aux->datos.litros);
    printf("Total: $%.2f\n", aux->datos.total);

    cabeza = cabeza->siguiente;

    if (cabeza == NULL)
    {
        final = NULL;
    }

    free(aux);

    printf("Cliente atendido correctamente.\n");
}

typedef struct NodoPila
{
    Recipiente datos;
    struct NodoPila *siguiente;
} NodoPila;

NodoPila *tope = NULL;


// Agrega un recipiente a la pila
void push()
{
    NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));

    if (nuevo == NULL)
    {
        printf("No hay memoria disponible.\n");
        return;
    }

    printf("Nombre del sabor: ");
    scanf(" %[^\n]", nuevo->datos.sabor);

    printf("Cantidad de litros: ");
    scanf("%f", &nuevo->datos.litros);

    // El nuevo nodo apunta al antiguo tope
    nuevo->siguiente = tope;

    // Ahora el nuevo nodo pasa a ser el tope
    tope = nuevo;

    printf("Recipiente agregado correctamente.\n");
}
void pushRecipiente(Recipiente r)
{
    NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));

    if (nuevo == NULL)
    {
        printf("No hay memoria disponible.\n");
        return;
    }

    nuevo->datos = r;
    nuevo->siguiente = tope;
    tope = nuevo;
}
// Retira el recipiente que está en el tope de la pila
Recipiente pop()
{
    Recipiente aux;

    // Verificar si la pila está vacía
    if (tope == NULL)
    {
        printf("La pila esta vacia.\n");

        strcpy(aux.sabor, "");
        aux.litros = 0;

        return aux;
    }

    // Guardar la información del recipiente
    aux = tope->datos;

    // Guardar el nodo que se va a eliminar
    NodoPila *eliminar = tope;

    // Mover el tope al siguiente nodo
    tope = tope->siguiente;

    // Liberar la memoria del nodo eliminado
    free(eliminar);

    // Devolver el recipiente
    return aux;
}
// Calcula el total de litros disponibles de un sabor
float totalLitrosSabor(const char sabor[])
{
    NodoPila *auxiliar = NULL;
    float total = 0;

    while (tope != NULL)
    {
        Recipiente r = pop();

        if (strcmp(r.sabor, sabor) == 0)
        {
            total += r.litros;
        }

        NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));

        nuevo->datos = r;
        nuevo->siguiente = auxiliar;
        auxiliar = nuevo;
    }

    while (auxiliar != NULL)
    {
        Recipiente r = auxiliar->datos;

        pushRecipiente(r);

        NodoPila *eliminar = auxiliar;
        auxiliar = auxiliar->siguiente;
        free(eliminar);
    }

    return total;
}

// Busca y retira litros de recipientes (LIFO desde el tope)
void buscarRecipiente(const char sabor[], float litrosSolicitados)
{
    NodoPila *auxiliar = NULL;

    while (tope != NULL)
    {
        Recipiente r = pop();

        if (strcmp(r.sabor, sabor) == 0 && litrosSolicitados > 0)
        {
            if (r.litros > litrosSolicitados)
            {
                r.litros -= litrosSolicitados;
                litrosSolicitados = 0;
            }
            else
            {
                litrosSolicitados -= r.litros;
                r.litros = 0;
            }
        }

        if (r.litros > 0)
        {
            NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));

            nuevo->datos = r;
            nuevo->siguiente = auxiliar;
            auxiliar = nuevo;
        }
    }

    while (auxiliar != NULL)
    {
        Recipiente r = auxiliar->datos;

        pushRecipiente(r);

        NodoPila *eliminar = auxiliar;
        auxiliar = auxiliar->siguiente;

        free(eliminar);
    }
}

// Muestra todos los clientes en espera
void mostrarCola()
{
    NodoCliente *actual;

    if (cabeza == NULL)
    {
        printf("No hay clientes en espera.\n");
        return;
    }

    printf("\n----- CLIENTES EN ESPERA -----\n");

    actual = cabeza;

    while (actual != NULL)
    {
        printf("Nombre: %s\n", actual->datos.nombre);
        printf("Sabor: %s\n", actual->datos.sabor);
        printf("Litros: %.2f\n", actual->datos.litros);
        printf("Total: $%.2f\n\n", actual->datos.total);

        actual = actual->siguiente;
    }
}
// Muestra todos los recipientes disponibles
void mostrarPila()
{
    NodoPila *auxiliar = NULL;

    if (tope == NULL)
    {
        printf("La pila esta vacia.\n");
        return;
    }

    printf("\n----- RECIPIENTES DISPONIBLES -----\n");

    while (tope != NULL)
    {
        Recipiente r = pop();

        printf("Sabor: %s\n", r.sabor);
        printf("Litros: %.2f\n\n", r.litros);

        NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));

        nuevo->datos = r;
        nuevo->siguiente = auxiliar;
        auxiliar = nuevo;
    }

    while (auxiliar != NULL)
    {
        Recipiente r = auxiliar->datos;

        pushRecipiente(r);

        NodoPila *eliminar = auxiliar;
        auxiliar = auxiliar->siguiente;
        free(eliminar);
    }
}

void liberarMemoria()
{
    NodoCliente *auxCliente;
    NodoPila *auxPila;

    // Liberar la cola
    while (cabeza != NULL)
    {
        auxCliente = cabeza;
        cabeza = cabeza->siguiente;
        free(auxCliente);
    }

    final = NULL;

    // Liberar la pila
    while (tope != NULL)
    {
        auxPila = tope;
        tope = tope->siguiente;
        free(auxPila);
    }
}

int main()
{
    int opcion;

    do
    {
        printf("\n===== HELADERIA DONA PEPE =====\n");
        printf("1. Registrar recipiente\n");
        printf("2. Mostrar pila\n");
        printf("3. Registrar cliente\n");
        printf("4. Mostrar cola\n");
        printf("5. Atender cliente\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                push();
                break;

            case 2:
                mostrarPila();
                break;

            case 3:
                encolar();
                break;

            case 4:
                mostrarCola();
                break;

            case 5:
                desencolar();
                break;

            case 6:
                liberarMemoria();
                printf("Gracias por utilizar el sistema.\n");
                break;
                
            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 6);
}