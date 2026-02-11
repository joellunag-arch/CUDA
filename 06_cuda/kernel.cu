#include <cmath>
__global__ void productoExterno(int *d_vector, int *v, int *u, int n)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    


    if (id < n*n)
    {
        int i = id / n; 
        int j = id % n; 

        d_vector[id]=v[i]*u[j];
    }
}

extern "C" void probar_operaciones(int *d_vector, int *d_v, int *d_u, int n)
{
    int hilos = 1024;
    productoExterno<<<1, hilos>>>(d_vector,d_v, d_u, n);
}