#include <fmt/core.h>
#include <cuda_runtime.h>
#include <vector>

// Declaramos la función wrapper que escribiste en kernel.cu
extern "C" void probar_operaciones(int *d_vector, int h, int w);

int main()
{

    int N, w, h;
    w = 7;
    h = 10;

    N = w * h;

    int *d_vector;

    size_t size_bytes = N * sizeof(int);

    std::vector<int> h_vector(N, 0);

    cudaMalloc(&d_vector, size_bytes);

    probar_operaciones(d_vector, h, w);

    cudaMemcpy(h_vector.data(), d_vector, size_bytes, cudaMemcpyDeviceToHost);
    cudaFree(d_vector);

    // mostrar resultado

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fmt::print("{} ", h_vector[i * w + j]);
        }
        //salto de linea para la siguiente fila
        fmt::print("\n");
        
    }
}