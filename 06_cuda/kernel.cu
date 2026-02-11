#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cstdint> // Para std::uint8_t

#define RADIO 1 

// Cambiamos 'unsigned char' por 'std::uint8_t' para ser modernos
__global__ void blurKernel(std::uint8_t* input, std::uint8_t* output, int width, int height) {
    // ... EL CONTENIDO DEL KERNEL ES IDÉNTICO AL ANTERIOR ...
    // Solo asegúrate de que si usas tipos, sean uint8_t
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int numPixels = width * height;

    if (tid < numPixels) {
        int x = tid % width;
        int y = tid / width;
        int sumR = 0, sumG = 0, sumB = 0, count = 0;

        for (int dy = -RADIO; dy <= RADIO; dy++) {
            for (int dx = -RADIO; dx <= RADIO; dx++) {
                int nx = x + dx; 
                int ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    int neighborIndex = (ny * width + nx) * 4;
                    sumR += input[neighborIndex + 0];
                    sumG += input[neighborIndex + 1];
                    sumB += input[neighborIndex + 2];
                    count++;
                }
            }
        }
        int myIndex = tid * 4;
        output[myIndex + 0] = (std::uint8_t)(sumR / count);
        output[myIndex + 1] = (std::uint8_t)(sumG / count);
        output[myIndex + 2] = (std::uint8_t)(sumB / count);
        output[myIndex + 3] = input[myIndex + 3];
    }
}

extern "C" void aplicarBlurCUDA(std::uint8_t* host_pixels, int width, int height) {
    size_t imgSize = width * height * 4 * sizeof(std::uint8_t);
    std::uint8_t *d_in, *d_out;

    cudaMalloc(&d_in, imgSize);
    cudaMalloc(&d_out, imgSize);

    cudaMemcpy(d_in, host_pixels, imgSize, cudaMemcpyHostToDevice);

    int totalPixels = width * height;
    int blockSize = 256;
    int gridSize = (totalPixels + blockSize - 1) / blockSize;

    blurKernel<<<gridSize, blockSize>>>(d_in, d_out, width, height);
    cudaDeviceSynchronize();

    cudaMemcpy(host_pixels, d_out, imgSize, cudaMemcpyDeviceToHost);

    cudaFree(d_in);
    cudaFree(d_out);
}