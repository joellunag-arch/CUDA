__global__ void operaciones(int* vector, int height) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;

    if (id < height) {
        vector[id] = (id * 5)+10; 
    }
    
   
}

extern "C" void probar_operaciones(int* d_vector, int h) {
    int hilos = 256;
    int bloques = (h + hilos - 1) / hilos;
    
    operaciones<<<bloques, hilos>>>(d_vector, h);
}