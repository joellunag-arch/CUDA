#include <cuda_runtime.h>

// Recibimos INPUT (constante) y OUTPUT (donde escribimos)
__global__ void filtroBlur(int *input, int *output, int h, int w)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;

    if(id < h * w)
    {
        int sum = 0;
        int count = 0;
        
        int myY = id / w;
        int myX = id % w;

        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                int neighborX = myX + dx;
                int neighborY = myY + dy;

                if (neighborX >= 0 && neighborX < w && neighborY >= 0 && neighborY < h)
                {
                    // Convertimos coordenada 2D -> 1D para leer memoria
                    int neighborId = neighborY * w + neighborX;
                    
                    // IMPORTANTE: Leemos siempre de INPUT
                    sum += input[neighborId];
                    count++;
                }
            }
        }
        output[id] = sum / count;
    }
}

extern "C" void probar_operaciones(int *d_in, int *d_out, int h, int w)
{
    int totalHilos = h * w;
    int hilos = 256;
    int bloques = (totalHilos + hilos - 1) / hilos;
    
    filtroBlur<<<bloques, hilos>>>(d_in, d_out, h, w);
}