#include <iostream>
#include "BusquedaAEstrella.h"
//TODO gestion de errores y cierres por fallo

int main() {
    std::string ficherografo = "../data/Grafo";
    std::string ficheroheuristica = "../data/heuristica_O1F5";
    BusquedaAEstrella Busqueda(ficherografo,ficheroheuristica);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}