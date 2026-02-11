#include <fmt/core.h>
#include <cuda_runtime.h>
#include <vector>

// Declaramos la función wrapper que escribiste en kernel.cu
extern "C" void probar_operaciones(int *d_vector, int *d_v, int *d_u, int n);

int main()
{

    std::vector<int> v = {1, 2, 3, 4};
    std::vector<int> u = {2, 2, 2, 2};
    int n, N;
    n = v.size();
    N = n * n;
    size_t size_bytes = N * sizeof(int);
    size_t size_bytes_v = n * sizeof(int);

    std::vector<int> h_vector(N, 0);
    int *d_v, *d_u, *d_vector;

    cudaMalloc(&d_v, size_bytes_v);
    cudaMalloc(&d_u, size_bytes_v);
    cudaMalloc(&d_vector,size_bytes);

    cudaMemcpy(d_v, v.data(), size_bytes_v, cudaMemcpyHostToDevice);
    cudaMemcpy(d_u, u.data(), size_bytes_v, cudaMemcpyHostToDevice);
    probar_operaciones(d_vector,d_v, d_u, n);

    cudaMemcpy(h_vector.data(), d_vector, size_bytes, cudaMemcpyDeviceToHost);
    cudaFree(d_vector);
    cudaFree(d_v);
    cudaFree(d_u);

    // mostrar resultado

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fmt::print("{} ", h_vector[i * n + j]);
        }
        fmt::print("\n");
    }
}