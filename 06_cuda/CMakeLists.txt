cmake_minimum_required(VERSION 3.16)

# Bypass CUDA check for VS 2026 (Mantén esto, es vital para tu versión de VS)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -allow-unsupported-compiler")

# Es buena práctica poner los lenguajes aquí dentro
project(Cuda01 LANGUAGES CXX CUDA)

# --- PASO 1: Encontrar el Toolkit de NVIDIA explícitamente ---
find_package(CUDAToolkit REQUIRED)

find_package(fmt CONFIG REQUIRED)
#find_package(Stb REQUIRED)
#find_package(Freetype REQUIRED)
#find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

add_executable(cuda01
    main.cpp
    kernel.cu
)

# --- PASO 2: Enlazar usando el target moderno ---
target_link_libraries(cuda01 PRIVATE 
    fmt::fmt
    CUDA::cudart  # <--- CAMBIO CLAVE: Usar CUDA::cudart en vez de cudart
)