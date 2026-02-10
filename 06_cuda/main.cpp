#include <fmt/core.h>
#include <cuda_runtime.h>
#include <vector>

// Declaramos la función wrapper que escribiste en kernel.cu
extern "C" void probar_operaciones(int* d_vector, int h);

int main() {

    int N = 10 ;
    std::vector<int> h_vector(N, 0); // Vector en el host

    //funcion para llenar el vector con valores iniciales
    for (int i = 0; i < N; ++i) {
        h_vector[i] = i;
    }
    
    int* d_vector; // Puntero para el vector en el device
    size_t size_bytes = N * sizeof(int);

    // Reservar memoria en el device
    cudaMalloc(&d_vector, size_bytes);

    // Copiar datos del host al device
    cudaMemcpy(d_vector, h_vector.data(), size_bytes, cudaMemcpyHostToDevice);

    // Llamar a la función que ejecuta el kernel
    probar_operaciones(d_vector, N);

    // Copiar resultados del device al host
    cudaMemcpy(h_vector.data(), d_vector, size_bytes, cudaMemcpyDeviceToHost);

    // Liberar memoria en el device
    cudaFree(d_vector);

    // Mostrar resultados
    for (int i = 0; i < N; ++i) {
        fmt::print("Elemento {}: {}\n", i, h_vector[i]);
    }

    return 0;
}