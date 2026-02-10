__global__ void falsa_matriz_kernel(int* matriz_lineal, int ancho, int alto) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    
    int total_elementos = ancho * alto;

    if (id < total_elementos) {
        //  De 1D a 2D
        int fila = id / ancho;      // División entera
        int col  = id % ancho;      // El resto de la división
        
        // Queremos guardar la suma de coordenadas (ej: fila 2, col 3 = 5)
        // Pero debemos escribir en el array lineal 1D
        matriz_lineal[id] = fila + col;
        
        // Visualización mental:
        // Si ancho es 10.
        // Hilo 12: 12 / 10 = 1 (Fila 1)
        //          12 % 10 = 2 (Columna 2)
        // Está en la segunda fila, tercer elemento.
    }
}

extern "C" void probar_matriz_1d(int* d_matriz, int w, int h) {
    int total = w * h;
    int hilos = 256;
    int bloques = (total + hilos - 1) / hilos;
    
    falsa_matriz_kernel<<<bloques, hilos>>>(d_matriz, w, h);
}