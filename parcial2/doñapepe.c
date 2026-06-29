#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Definición de estructuras y constantes
#define MAX_SABORES 10
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

#define MAX_CLIENTES 50

Cliente cola[MAX_CLIENTES];

int cabeza = 0;   // Índice del primer cliente
int final = -1;   // Índice del último cliente

float totalLitrosSabor(const char sabor[]);
void buscarRecipiente(const char sabor[], float litrosSolicitados);

// Agrega un nuevo cliente a la cola
void encolar()
{
    if (final == MAX_CLIENTES - 1)
    {
        printf("La cola esta llena.\n");
        return;
    }

    final++;

    printf("Nombre del cliente: ");
    scanf(" %[^\n]", cola[final].nombre);

    printf("Sabor: ");
    scanf(" %[^\n]", cola[final].sabor);

    printf("Cantidad de litros: ");
    scanf("%f", &cola[final].litros);

     // Precio: 8000 por litro
    cola[final].total = cola[final].litros * 8000;

    printf("Cliente registrado correctamente.\n");
}

// Atiende al primer cliente de la cola
void desencolar()
{
    if (cabeza > final)
    {
        printf("No hay clientes en espera.\n");
        return;
    }

    printf("\n--- ATENDIENDO CLIENTE ---\n");

    float litrosDisponibles = totalLitrosSabor(cola[cabeza].sabor);

    if (litrosDisponibles == 0)
    {
        printf("No hay ese sabor disponible.\n");
        return;
    }

    if (litrosDisponibles < cola[cabeza].litros)
    {
        printf("No hay suficientes litros de ese sabor.\n");
        return;
    }

    // Retira los litros de los recipientes
    buscarRecipiente(cola[cabeza].sabor, cola[cabeza].litros);

    printf("Nombre: %s\n", cola[cabeza].nombre);
    printf("Sabor: %s\n", cola[cabeza].sabor);
    printf("Cantidad: %.2f litros\n", cola[cabeza].litros);
    printf("Total: $%.2f\n", cola[cabeza].total);

    cabeza++;

    printf("Cliente atendido correctamente.\n");
}

Recipiente pila[MAX_SABORES];



int tope = -1;  // Índice del último recipiente

// Agrega un recipiente a la pila
void push()
{
    if (tope == MAX_SABORES - 1)
    {
        printf("La pila esta llena.\n");
        return;
    }

    tope++;

    printf("Nombre del sabor: ");
    scanf(" %[^\n]", pila[tope].sabor);

    printf("Cantidad de litros: ");
    scanf("%f", &pila[tope].litros);

    printf("Recipiente agregado correctamente.\n");
}
Recipiente pop()
{
    Recipiente aux;

    if (tope == -1)
    {
        printf("La pila esta vacia.\n");
        strcpy(aux.sabor, "");
        aux.litros = 0;
        return aux;
    }

    aux = pila[tope];
    tope--;

    return aux;
}
// Calcula el total de litros disponibles de un sabor
float totalLitrosSabor(const char sabor[])
{
    Recipiente auxiliar[MAX_SABORES];
    int topeAux = -1;

    float total = 0;

    while (tope != -1)
    {
        Recipiente r = pop();

        if (strcmp(r.sabor, sabor) == 0)
        {
            total += r.litros;
        }

        auxiliar[++topeAux] = r;
    }

    while (topeAux != -1)
    {
        pila[++tope] = auxiliar[topeAux];
        topeAux--;
    }

    return total;
}

// Busca y retira litros de recipientes (LIFO desde el tope)
void buscarRecipiente(const char sabor[], float litrosSolicitados)
{
    Recipiente auxiliar[MAX_SABORES];
    int topeAux = -1;

    while (tope != -1)
    {
        Recipiente r = pop();

        if (strcmp(r.sabor, sabor) == 0 && litrosSolicitados > 0)
        {
            if (r.litros > litrosSolicitados)
            {
                r.litros -= litrosSolicitados;
                litrosSolicitados = 0;

                pila[++tope] = r;
            }
            else
            {
                litrosSolicitados -= r.litros;

                if (litrosSolicitados < 0)
                {
                    r.litros = -litrosSolicitados;
                    litrosSolicitados = 0;
                    pila[++tope] = r;
                }
            }
        }
        else
        {
            auxiliar[++topeAux] = r;
        }
    }

    while (topeAux != -1)
    {
        pila[++tope] = auxiliar[topeAux];
        topeAux--;
    }
}
// Muestra todos los clientes en espera
void mostrarCola()
{
    int i;

    if (cabeza > final)
    {
        printf("No hay clientes en espera.\n");
        return;
    }

    printf("\n----- CLIENTES EN ESPERA -----\n");

    for (i = cabeza; i <= final; i++)
    {
        printf("Nombre: %s\n", cola[i].nombre);
        printf("Sabor: %s\n", cola[i].sabor);
        printf("Litros: %.2f\n", cola[i].litros);
        printf("Total: $%.2f\n\n", cola[i].total);
    }
}
// Muestra todos los recipientes disponibles
void mostrarPila()
{
    Recipiente auxiliar[MAX_SABORES];
    int topeAux = -1;

    if (tope == -1)
    {
        printf("La pila esta vacia.\n");
        return;
    }

    printf("\n------ PILA DE RECIPIENTES ------\n");

    while (tope != -1)
    {
        Recipiente r = pop();

        printf("Sabor: %s\n", r.sabor);
        printf("Litros: %.2f\n\n", r.litros);

        auxiliar[++topeAux] = r;
    }

    while (topeAux != -1)
    {
        pila[++tope] = auxiliar[topeAux];
        topeAux--;
    }
}
// Menú principal del sistema
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
                printf("Gracias por utilizar el sistema.\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 6);
}