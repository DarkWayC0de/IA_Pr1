//
// Created by darkwayc0de on 11/10/19.
//

#ifndef PR1_BUSQUEDAAESTRELLA_H
#define PR1_BUSQUEDAAESTRELLA_H


#include "Grafo.h"

class BusquedaAEstrella {
 public:
    BusquedaAEstrella(const std::string& NombreFicheroGrafo, const std::string& NombreFicheroHeuristica);
    ~BusquedaAEstrella();

 private:
    Grafo Grafo_problema_;
    std::vector<double> Heuristica_Problema_;
    void Cargar_datos_heuristica(const std::string& NombreFicheroHeuristica);


};


#endif //PR1_BUSQUEDAAESTRELLA_H
