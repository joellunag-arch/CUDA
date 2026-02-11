cmake_minimum_required(VERSION 3.16)

# Bypass CUDA check for VS (Mantén esto, es vital para tu versión de VS)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -allow-unsupported-compiler")

# Definición del proyecto y lenguajes
project(Cuda01 LANGUAGES CXX CUDA)

# --- PASO 1: Encontrar Paquetes ---
find_package(CUDAToolkit REQUIRED)
find_package(fmt CONFIG REQUIRED)

# Añadimos SFML. Para el examen solo necesitas Graphics, Window y System.
# Si usas vcpkg, el modo CONFIG es el correcto.
find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

# Definición del ejecutable
add_executable(cuda01
    main.cpp
    kernel.cu
)

# --- PASO 2: Enlazar Librerías ---
target_link_libraries(cuda01 PRIVATE 
    fmt::fmt
    CUDA::cudart 
    SFML::Graphics  
    SFML::Window
    SFML::System
)

