#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include "taller7.h"

int main() {
    char productos[5][30], recursos[4][30];
    int tiempo[5];
    int recursosPorProducto[5][4] = {0};
    int stock[4] = {0};
    int demanda[5] = {0};
    bool activo[5] = {true, true, true, true, true}; // Todos los productos inicialmente activos
    int opcion;

    ingresarRecursos(recursos, stock);
    ingresarProductos(productos, tiempo, recursosPorProducto, recursos, activo);

    do {
        opcion = menu();
        switch(opcion) {
            case 1:
                ingresarDemanda(demanda, productos, tiempo, recursosPorProducto, stock, recursos, activo);
                break;
            case 2:
                mostrarProducto(productos, tiempo, recursosPorProducto, recursos, activo);
                break;
            case 3:
                editarProducto(productos, tiempo, recursosPorProducto, recursos, activo);
                break;
            case 4:
                mostrarRecursos(recursos, stock);
                break;
            case 5:
                editarRecursos(recursos, stock);
                break;
            case 6:
                eliminarProducto(productos, activo);
                break;
            case 7:
                printf("\nSaliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 7);

return 0;
}
