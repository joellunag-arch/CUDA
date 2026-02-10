#include <cstdio> 
#include <cuda_runtime.h>

__global__ void quien_soy_kernel() {
    // 1. Calcular coordenadas locales y globales
    int b_id = blockIdx.x;    // ¿En qué bloque estoy?
    int t_id = threadIdx.x;   // ¿Quién soy dentro del bloque?
    int dim  = blockDim.x;    // ¿Cuántos somos por bloque?

    // 2. La Fórmula Maestra
    int global_id = b_id * dim + t_id;

    // Solo imprimimos los primeros 10 hilos para no saturar la consola
    if (global_id < 10) {
        printf("Bloque: %d | Hilo Local: %d | ID Global: %d\n", b_id, t_id, global_id);
    }
}

extern "C" void lanzar_quien_soy() {
    // Lanzamos 2 bloques de 5 hilos cada uno
    // Total hilos esperados: 10
    quien_soy_kernel<<<2, 5>>>();
    cudaDeviceSynchronize(); // Esperar a que impriman
}