cmake_minimum_required(VERSION 3.14)
project(Pr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pr1 src/main.cpp src/Grafo.cpp src/Grafo.h src/BusquedaAEstrella.cpp src/BusquedaAEstrella.h src/NodoArbol.cpp src/NodoArbol.h src/Arbol.cpp src/Arbol.h)
add_executable(Pr1analisis src/main2.cpp src/Grafo.cpp src/Grafo.h src/BusquedaAEstrella.cpp src/BusquedaAEstrella.h src/NodoArbol.cpp src/NodoArbol.h src/Arbol.cpp src/Arbol.h)
