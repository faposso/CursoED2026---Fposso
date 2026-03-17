#include <stdio.h>
#include "areas.h"
#include "volumenes.h"


int main() {
    int opcion;
    float valor;

    do {
        printf("\n===== CALCULADORA DE AREAS Y VOLUMENES =====\n");
        printf("1. Calcular area del circulo\n");
        printf("2. Calcular area del cuadrado\n");
        printf("3. Calcular volumen de la esfera\n");
        printf("4. Calcular volumen del cubo\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion (1-5): ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("\n--- Area del Circulo ---\n");
                printf("Ingresa el radio (en cm): ");
                scanf("%f", &valor);
                if (valor > 0) {
                    printf("Resultado: El area del circulo es %.2f cm²\n", area_circulo(valor));
                } else {
                    printf("Error: El radio debe ser un numero positivo.\n");
                }
                break;
            case 2:
                printf("\n--- Area del Cuadrado ---\n");
                float lado;
                printf("Ingresa el lado (en cm): ");
                scanf("%f", &lado);

                if (lado > 0) {
                    printf("Resultado: El area del cuadrado es %.2f cm²\n", area_cuadrado(lado, lado));
                } else {
                    printf("Error: El lado debe ser un numero positivo.\n");
                }
                break;
            case 3:
                printf("\n--- Volumen de la Esfera ---\n");
                printf("Ingresa el radio (en cm): ");
                scanf("%f", &valor);
                if (valor > 0) {
                    printf("Resultado: El volumen de la esfera es %.2f cm³\n", volumen_esfera(valor));
                } else {
                    printf("Error: El radio debe ser un numero positivo.\n");
                }
                break;
            case 4:
                printf("\n--- Volumen del Cubo ---\n");
                printf("Ingresa el lado (en cm): ");
                scanf("%f", &valor);
                if (valor > 0) {
                    printf("Resultado: El volumen del cubo es %.2f cm³\n", volumen_cubo(valor));
                } else {
                    printf("Error: El lado debe ser un numero positivo.\n");
                }
                break;
            case 5:
                printf("\n¡Gracias por usar la calculadora! Saliendo...\n");
                break;
            default:
                printf("\nError: Opcion inválida. Por favor, selecciona una opcion del 1 al 5.\n");
        }
    } while(opcion != 5);

    return 0;
}
