__global__ void llenarMatriz(int* vector, int h, int w) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int N= h*w;


    if (id < N) {

        if((id/w)==(id%w)){
            vector[id]=1;
        }else{
            vector[id]=0;
        }
        
    }
    
   
}

extern "C" void probar_operaciones(int* d_vector, int h,int w) {
    int hilos = 1024;
    int bloques = (h*w + hilos - 1) / hilos;
    
    llenarMatriz<<<bloques, hilos>>>(d_vector, h,w);
}