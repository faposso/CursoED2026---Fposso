#include <stdio.h>
#include "areas.h"
#include "volumenes.h"

#define PI 3.1415

float area_circulo(float radio) {
    return PI * radio * radio;
}

float area_cuadrado(float base, float altura) {
    return base * altura;
}

float volumen_esfera(float radio) {
    return (4.0 / 3.0) * PI * radio * radio * radio;
}

float volumen_cubo(float lado) {
    return lado * lado * lado;
}

int main() {
    int opcion;
    float valor;

    do {
        printf("\n===== CALCULADORA DE AREAS Y VOLUMENES =====\n");
        printf("1. Calcular area del circulo\n");
        printf("2. Calcular area del mcuadrado\n");
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
                float base, altura;
                printf("Ingresa la base (en cm): ");
                scanf("%f", &base);
                printf("Ingresa la altura (en cm): ");
                scanf("%f", &altura);
                
                if (base > 0 && altura > 0) {
                    printf("Resultado: El area del cuadrado es %.2f cm²\n", area_cuadrado(base, altura));
                } else {
                    printf("Error: La base y altura deben ser numeros positivos.\n");
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