#include <fmt/core.h>
#include <cuda_runtime.h>
#include <vector>

// Declaramos la función wrapper que escribiste en kernel.cu
extern "C" void probar_matriz_1d(int* d_matriz, int w, int h);

int main() {
    // 1. Configuración de la "Matriz"
    // Usamos 8x8 para que sea fácil de visualizar en la consola
    int width = 8;
    int height = 8;
    int total_elements = width * height;
    size_t size_bytes = total_elements * sizeof(int);

    fmt::print("--- Inicio Test Ejercicio 3: Mapeo 1D a 2D ---\n");
    fmt::print("Dimensiones: {} x {} (Total: {} elementos)\n", width, height, total_elements);

    // 2. Memoria en HOST (CPU)
    // Usamos std::vector para no preocuparnos por el delete[] manual
    std::vector<int> h_matrix(total_elements, 0);

    // 3. Memoria en DEVICE (GPU)
    int* d_matrix;
    cudaMalloc(&d_matrix, size_bytes);

    // NOTA: No hacemos cudaMemcpy Host->Device porque el kernel 
    // va a SOBREESCRIBIR todos los valores calculando (fila + columna).
    // No necesita datos de entrada, solo espacio.

    // 4. Invocar el Kernel
    // La GPU llenará el vector lineal simulando ser una matriz 2D
    probar_matriz_1d(d_matrix, width, height);

    // Comprobar errores de lanzamiento (buena práctica)
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        fmt::print("Error en kernel: {}\n", cudaGetErrorString(err));
    }

    // 5. Copiar resultados Device -> Host
    cudaMemcpy(h_matrix.data(), d_matrix, size_bytes, cudaMemcpyDeviceToHost);

    // 6. Visualización y Verificación
    // El vector 'h_matrix' es plano (1D), pero nosotros lo imprimimos
    // usando dos bucles para ver si la estructura 2D es correcta.
    fmt::print("\nMatriz Resultante (Valor esperado = Fila + Columna):\n");
    
    for (int y = 0; y < height; y++) {
        fmt::print("Fila {}: [ ", y);
        for (int x = 0; x < width; x++) {
            // EL TRUCO INVERSO: De Coordenadas (y,x) a Índice Lineal
            // Esta fórmula es la recíproca de lo que hiciste en el kernel
            int linear_index = y * width + x;
            
            // Imprimimos el valor recuperado
            fmt::print("{:2} ", h_matrix[linear_index]);
        }
        fmt::print("]\n");
    }

    // 7. Liberar memoria GPU
    cudaFree(d_matrix);

    fmt::print("\n--- Fin del Test ---\n");
    return 0;
}