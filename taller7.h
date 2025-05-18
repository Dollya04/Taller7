int menu();
void ingresarRecursos(char recursos[4][30], int *stock);
void ingresarProductos(char productos[5][30], int *tiempo, int recursosPorProducto[5][4], char recursos[4][30], bool *activo);
void ingresarDemanda(int *demanda, char productos[5][30], int *tiempo, int recursosPorProducto[5][4], int *stock, char recursos[4][30], bool *activo);
void mostrarProducto(char productos[5][30], int *tiempo, int recursosPorProducto[5][4], char recursos[4][30], bool *activo);
void editarProducto(char productos[5][30], int *tiempo, int recursosPorProducto[5][4], char recursos[4][30], bool *activo);
void mostrarRecursos(char recursos[4][30], int *stock);
void editarRecursos(char recursos[4][30], int *stock);
void eliminarProducto(char productos[5][30], bool *activo);