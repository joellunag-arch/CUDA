#include <fmt/core.h>
#include <cuda_runtime.h>
#include <vector>


extern "C" void probar_operaciones(int *d_in, int *d_out, int h, int w);

int main()
{
    int h = 4;
    int w = 4;
    int N = h * w;
    size_t size_bytes = N * sizeof(int);

    // Vector original en CPU
    std::vector<int> h_in(N);
    // Vector resultado en CPU
    std::vector<int> h_out(N);

    // Llenamos con valores (1, 2, 3...)
    for (int i = 0; i < N; i++) {
        h_in[i] = i + 1;
    }

    //imprimimos la matriz original
    fmt::print("Matriz Original:\n");
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fmt::print("{:2} ", h_in[i * w + j]);
        }
        fmt::print("\n");
    }

    // Punteros GPU
    int *d_in, *d_out;
    cudaMalloc(&d_in, size_bytes);
    cudaMalloc(&d_out, size_bytes); // CORRECCIÓN 2: Memoria para salida

    // Copiamos SOLO la entrada
    cudaMemcpy(d_in, h_in.data(), size_bytes, cudaMemcpyHostToDevice);

    // Llamamos al kernel pasando entrada y salida por separado
    probar_operaciones(d_in, d_out, h, w);

    // Recuperamos SOLO la salida
    cudaMemcpy(h_out.data(), d_out, size_bytes, cudaMemcpyDeviceToHost);

    // Liberamos memoria
    cudaFree(d_in);
    cudaFree(d_out);

    // Imprimimos la matriz RESULTANTE (Blur)
    fmt::print("Matriz con Blur:\n");
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fmt::print("{:2} ", h_out[i * w + j]);
        }
        fmt::print("\n");
    }
}