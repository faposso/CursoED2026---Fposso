#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Autores:
- yair Andrés Tapiero Gil
- Juan Manuel cortes Paniagua
- Frank Andry Posso Hurtado
*/

#define MAX_CONTENEDORES 30

void registrarPesos(int pesos[], int *n, int *ordenado);
void generarAleatorios(int pesos[], int *n, int *ordenado);
void mostrarPesos(int pesos[], int n);

void quickSort(int arr[], int low, int high);
int particion(int arr[], int low, int high);

void mergeSort(int arr[], int izquierda, int derecha);
void merge(int arr[], int izquierda, int medio, int derecha);

void shellSort(int arr[], int n);

int busquedaBinaria(int arr[], int n, int valor);

int main() {
    int pesos[MAX_CONTENEDORES];
    int cantidad = 0;
    int ordenado = 0;
    int opcion;

    srand(time(NULL));

    do {
        printf("\n========================================\n");
        printf("SISTEMA DE ORGANIZACION DE CONTENEDORES\n");
        printf("MUELLE DE CARGA\n");
        printf("========================================\n");
        printf("1. Registrar peso de contenedores manualmente\n");
        printf("2. Generar pesos aleatorios de contenedores\n");
        printf("3. Mostrar contenedores registrados\n");
        printf("4. Ordenar contenedores Metodo 1 (Quick Sort)\n");
        printf("5. Ordenar contenedores Metodo 2 (Merge Sort)\n");
        printf("6. Ordenar contenedores Metodo 3 (Shell Sort)\n");
        printf("7. Buscar contenedor\n");
        printf("8. Salir\n");
        printf("\n========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {

            case 1:
                registrarPesos(pesos, &cantidad, &ordenado);
                break;

            case 2:
                generarAleatorios(pesos, &cantidad, &ordenado);
                break;

            case 3:
                mostrarPesos(pesos, cantidad);
                break;

            case 4:
                if(cantidad > 0) {
                    quickSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("Arreglo ordenado con Quick Sort.\n");
                }
                break;

            case 5:
                if(cantidad > 0) {
                    mergeSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("Arreglo ordenado con Merge Sort.\n");
                }
                break;

            case 6:
                if(cantidad > 0) {
                    shellSort(pesos, cantidad);
                    ordenado = 1;
                    printf("Arreglo ordenado con Shell Sort.\n");
                }
                break;

            case 7: {
                if(!ordenado) {
                    printf("Debe ordenar primero el arreglo.\n");
                    break;
                }

                int pesoBuscar;
                printf("Ingrese el peso a buscar: ");
                scanf("%d", &pesoBuscar);

                int posicion = busquedaBinaria(pesos, cantidad, pesoBuscar);

                if(posicion != -1)
                    printf("Contenedor encontrado en la posicion %d\n", posicion);
                else
                    printf("Contenedor no encontrado.\n");

                break;
            }

            case 8:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 8);

    return 0;
}

void registrarPesos(int pesos[], int *n, int *ordenado) {

    printf("Cantidad de contenedores (max 30): ");
    scanf("%d", n);

    if(*n > MAX_CONTENEDORES)
        *n = MAX_CONTENEDORES;

    for(int i = 0; i < *n; i++) {
        printf("Peso contenedor %d: ", i + 1);
        scanf("%d", &pesos[i]);
    }

    *ordenado = 0;
}

void generarAleatorios(int pesos[], int *n, int *ordenado) {

    printf("Cantidad de contenedores (max 30): ");
    scanf("%d", n);

    if(*n > MAX_CONTENEDORES)
        *n = MAX_CONTENEDORES;

    for(int i = 0; i < *n; i++) {
        pesos[i] = rand() % 30001 + 1000;
    }

    printf("Pesos generados correctamente.\n");

    *ordenado = 0;
}

void mostrarPesos(int pesos[], int n) {

    if(n == 0) {
        printf("No hay contenedores registrados.\n");
        return;
    }

    printf("\nLista de pesos:\n");

    for(int i = 0; i < n; i++) {
        printf("%d kg\n", pesos[i]);
    }
}

int particion(int arr[], int low, int high) {

    int pivote = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {

        if(arr[j] <= pivote) {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {

    if(low < high) {

        int pi = particion(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int izquierda, int medio, int derecha) {

    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    if (!L || !R) {
        fprintf(stderr, "Error de memoria en merge\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n1; i++)
        L[i] = arr[izquierda + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    while(i < n1 && j < n2) {

        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int izquierda, int derecha) {

    if(izquierda < derecha) {

        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSort(arr, izquierda, medio);
        mergeSort(arr, medio + 1, derecha);

        merge(arr, izquierda, medio, derecha);
    }
}

void shellSort(int arr[], int n) {

    for(int gap = n / 2; gap > 0; gap /= 2) {

        for(int i = gap; i < n; i++) {

            int temp = arr[i];
            int j;

            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    }
}

int busquedaBinaria(int arr[], int n, int valor) {

    int izquierda = 0;
    int derecha = n - 1;

    while(izquierda <= derecha) {

        int medio = (izquierda + derecha) / 2;

        if(arr[medio] == valor)
            return medio;

        if(arr[medio] < valor)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }

    return -1;
}