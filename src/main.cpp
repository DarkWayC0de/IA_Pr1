#include <iostream>
#include "BusquedaAEstrella.h"


int main() {
    std::string ficherografo = "../data/Grafo";
    std::string ficheroheuristica = "../data/heuristica_O1F5";
    BusquedaAEstrella Busqueda(ficherografo,ficheroheuristica);
    int const ORIGEN =1;
    int const DESTINO = 5;
    auto resultado = Busqueda.realizarBusquedaAEstrella(ORIGEN-1, DESTINO -1);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}