#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "taller7.h"

int menu() {
    int opc;
    printf("\n--- MENU ---\n");
    printf("1. Ingresar pedido y ver lo requerido\n");
    printf("2. Mostrar productos\n");
    printf("3. Editar producto\n");
    printf("4. Mostrar recursos\n");
    printf("5. Editar recurso\n");
    printf("6. Eliminar producto\n");
    printf("7. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    return opc;
}

void ingresarRecursos(char recursos[4][30], int *stock) {
    for (int i = 0; i < 4; i++) {
        printf("\n--- Recurso %d ---\n", i + 1);
        printf("Nombre: ");
        fflush(stdin);
        fgets(recursos[i], 30, stdin);
        recursos[i][strcspn(recursos[i], "\n")] = 0;

        do {
            printf("Stock disponible de %s: ", recursos[i]);
        } while (scanf("%d", &stock[i]) != 1 || stock[i] < 0);
    }
}

void ingresarProductos(char productos[5][30], int *tiempo, int recursosPorProducto[5][4], char recursos[4][30], bool *activo) {
    for (int i = 0; i < 5; i++) {
        activo[i] = true; 
        printf("\n--- Producto %d ---\n", i + 1);
        printf("Nombre: ");
        fflush(stdin);
        fgets(productos[i], 30, stdin);
        productos[i][strcspn(productos[i], "\n")] = 0;

        do {
            printf("Tiempo de fabricacion (min): ");
        } while (scanf("%d", &tiempo[i]) != 1 || tiempo[i] <= 0);

        for (int j = 0; j < 4; j++) {
            printf("Cantidad de recurso '%s' requerido por unidad: ", recursos[j]);
            do {
                scanf("%d", &recursosPorProducto[i][j]);
            } while (recursosPorProducto[i][j] < 0);
        }
    }
}

void ingresarDemanda(int *demanda, char productos[5][30], int *tiempo, int recursosPorProducto[5][4], int *stock, char recursos[4][30], bool *activo) {
    char buscar[30];
    int cantidad, tiempoLimite;
    int encontrado = -1;

    printf("\n--- NUEVO PEDIDO ---\n");
    printf("Ingrese el nombre del producto a solicitar: ");
    fflush(stdin);
    fgets(buscar, 30, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    for (int i = 0; i < 5; i++) {
        if (activo[i] && strcmp(productos[i], buscar) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Producto no encontrado o ha sido eliminado.\n");
        return;
    }

    do {
        printf("Ingrese la cantidad a solicitar de '%s': ", productos[encontrado]);
    } while (scanf("%d", &cantidad) != 1 || cantidad <= 0);

    do {
        printf("Ingrese el tiempo limite de entrega en minutos: ");
    } while (scanf("%d", &tiempoLimite) != 1 || tiempoLimite <= 0);

    int tiempoTotal = tiempo[encontrado] * cantidad;
    bool recursosSuficientes = true;
    bool tiempoSuficiente = tiempoTotal <= tiempoLimite;

    printf("\n Completando pedido...\n");
    printf("Producto: %s\n", productos[encontrado]);
    printf("Tiempo total requerido: %d minutos\n", tiempoTotal);
    printf("Tiempo disponible: %d minutos\n", tiempoLimite);

    for (int j = 0; j < 4; j++) {
        int requerido = recursosPorProducto[encontrado][j] * cantidad;
        printf("Recurso '%s': requerido = %d | disponible = %d\n", recursos[j], requerido, stock[j]);
        if (requerido > stock[j]) {
            recursosSuficientes = false;
        }
    }

    if (tiempoSuficiente && recursosSuficientes) {
        printf("Pedido ACEPTADO. Fabricacion iniciada.\n");
        for (int j = 0; j < 4; j++) {
            stock[j] -= recursosPorProducto[encontrado][j] * cantidad;
        }
        demanda[encontrado] += cantidad;
    } else {
        printf("Pedido RECHAZADO. Motivos:\n");
        if (!tiempoSuficiente) printf("- Tiempo insuficiente.\n");
        if (!recursosSuficientes) printf("- Recursos insuficientes.\n");
    }
}

void mostrarProducto(char productos[5][30], int *tiempo, int recursosPorProducto[5][4], char recursos[4][30], bool *activo) {
    for (int i = 0; i < 5; i++) {
        if (!activo[i]) continue;
        printf("\nProducto %d: %s", i + 1, productos[i]);
        printf("\nTiempo de fabricacion: %d minutos", tiempo[i]);
        for (int j = 0; j < 4; j++) {
            printf("\nRecurso %s: %d por unidad", recursos[j], recursosPorProducto[i][j]);
        }
        printf("\n");
    }
}

void editarProducto(char productos[5][30], int *tiempo, int recursosPorProducto[5][4], char recursos[4][30], bool *activo) {
    char buscar[30];
    printf("\nIngrese el nombre del producto a editar: ");
    fflush(stdin);
    fgets(buscar, 30, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    for (int i = 0; i < 5; i++) {
        if (activo[i] && strcmp(productos[i], buscar) == 0) {
            printf("Editando producto: %s\n", productos[i]);
            printf("Nuevo nombre: ");
            fflush(stdin);
            fgets(productos[i], 30, stdin);
            productos[i][strcspn(productos[i], "\n")] = 0;

            printf("Nuevo tiempo de fabricacion: ");
            scanf("%d", &tiempo[i]);

            for (int j = 0; j < 4; j++) {
                printf("Cantidad de recurso '%s' requerido por unidad: ", recursos[j]);
                scanf("%d", &recursosPorProducto[i][j]);
            }
            return;
        }
    }
    printf("Producto no encontrado o eliminado.\n");
}

void mostrarRecursos(char recursos[4][30], int *stock) {
    printf("\n--- STOCK DE RECURSOS ---\n");
    for (int i = 0; i < 4; i++) {
        printf("Recurso %d: %s | Stock: %d\n", i + 1, recursos[i], stock[i]);
    }
}

void editarRecursos(char recursos[4][30], int *stock) {
    char buscar[30];
    printf("\nIngrese el nombre del recurso a editar: ");
    fflush(stdin);
    fgets(buscar, 30, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    for (int i = 0; i < 4; i++) {
        if (strcmp(recursos[i], buscar) == 0) {
            printf("Editando recurso: %s\n", recursos[i]);
            printf("Nuevo nombre: ");
            fflush(stdin);
            fgets(recursos[i], 30, stdin);
            recursos[i][strcspn(recursos[i], "\n")] = 0;

            printf("Nuevo stock: ");
            scanf("%d", &stock[i]);
            return;
        }
    }
    printf("Recurso no encontrado.\n");
}

void eliminarProducto(char productos[5][30], bool *activo) {
    char buscar[30];
    printf("\nIngrese el nombre del producto a eliminar: ");
    fflush(stdin);
    fgets(buscar, 30, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    for (int i = 0; i < 5; i++) {
        if (strcmp(productos[i], buscar) == 0 && activo[i]) {
            activo[i] = false;
            printf("Producto '%s' eliminado correctamente.\n", productos[i]);
            return;
        }
    }
    printf("Producto no encontrado o ya eliminado.\n");
}