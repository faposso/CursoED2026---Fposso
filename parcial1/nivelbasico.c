//ordenamiento por burbuja
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                printf("Paso: ", i+1);
                printArray(arr, n);
            }
        }
    }
}

//ordenamiento por seleccion
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        printf("Paso: ", i+1);
        printArray(arr, n);
    }
}

//ordenamiento por insercion
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
        printf("Paso: ", i);
        printArray(arr, n);
    }
}

#include <stdio.h>
#include <stdlib.h>

// Función auxiliar para imprimir el arreglo
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int original[100];
    int n = 0;
    int dataEntered = 0;
    int opcion;

    do {
        printf("\nMenu de opciones:\n");
        if (!dataEntered) {
            printf("1. Registrar datos en el vector\n");
            printf("6. Salir\n");
        } else {
            printf("1. Registrar datos en el vector\n");
            printf("2. Mostrar el arreglo original\n");
            printf("3. Ordenar mediante metodo Burbuja\n");
            printf("4. Ordenar mediante metodo Seleccion\n");
            printf("5. Ordenar mediante metodo Insercion\n");
            printf("6. Salir\n");
        }
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                printf("Ingrese el numero de elementos (max 100): ");
                scanf("%d", &n);
                if (n > 100) n = 100;
                for (int i = 0; i < n; i++) {
                    printf("Elemento %d: ", i + 1);
                    scanf("%d", &original[i]);
                }
                dataEntered = 1;
                break;
            }
            case 2: {
                if (dataEntered) {
                    printf("Arreglo original: ");
                    for (int i = 0; i < n; i++) {
                        printf("%d ", original[i]);
                    }
                    printf("\n");
                } else {
                    printf("No hay datos registrados.\n");
                }
                break;
            }
            case 3: {
                if (dataEntered) {
                    int temp[100];
                    for (int i = 0; i < n; i++) temp[i] = original[i];
                    bubbleSort(temp, n);
                    printf("Arreglo ordenado por burbuja: ");
                        for (int i = 0; i < n; i++) {
                            printf("%d ", temp[i]);
                        }
                        printf("\n");
                } else {
                    printf("No hay datos registrados.\n");
                }
                break;
            }
            case 4: {
                if (dataEntered) {
                    int temp[100];
                    for (int i = 0; i < n; i++) temp[i] = original[i];
                    selectionSort(temp, n);
                    printf("Arreglo ordenado por seleccion: ");
                    for (int i = 0; i < n; i++) {
                        printf("%d ", temp[i]);
                    }
                    printf("\n");
                } else {
                    printf("No hay datos registrados.\n");
                }
                break;
            }
            case 5: {
                if (dataEntered) {
                    int temp[100];
                    for (int i = 0; i < n; i++) temp[i] = original[i];
                    insertionSort(temp, n);
                    printf("Arreglo ordenado por insercion: ");
                    for (int i = 0; i < n; i++) {
                        printf("%d ", temp[i]);
                    }
                    printf("\n");
                } else {
                    printf("No hay datos registrados.\n");
                }
                break;
            }
            case 6: {
                printf("Saliendo...\n");
                break;
            }
            default: {
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}