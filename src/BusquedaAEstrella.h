//
// Created by darkwayc0de on 11/10/19.
//

#ifndef PR1_BUSQUEDAAESTRELLA_H
#define PR1_BUSQUEDAAESTRELLA_H

#include <set>
#include "Grafo.h"
#include "NodoArbol.h"
#include "Arbol.h"

class BusquedaAEstrella {
 public:
    BusquedaAEstrella(const std::string& NombreFicheroGrafo, const std::string& NombreFicheroHeuristica);
    ~BusquedaAEstrella();
    std::pair<double ,std::vector<unsigned >> realizarBusquedaAEstrella(unsigned origen, unsigned destino);

 private:
    Grafo Grafo_problema_;
    std::vector<double> Heuristica_Problema_;
    unsigned Origen_;
    Arbol arbol_;
    void cargar_datos_heuristica(const std::string& NombreFicheroHeuristica);
    std::vector<std::shared_ptr<NodoArbol>> generarHijos(const std::shared_ptr<NodoArbol>& padre,
                                                         std::set<std::shared_ptr<NodoArbol>>& nodosAEvaluar);
    std::pair<double ,std::vector<unsigned >> analizarGenerarArbol(std::shared_ptr<NodoArbol> &nodo,
                                                                    unsigned destino);
    void  analizarGenerarArbolRecursivo(std::shared_ptr<NodoArbol> &nodo,
                                        unsigned destino,
                                        double &costeMinimoActual,
                                        std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar,
                                        std::vector<unsigned >& camino);

    bool pertenese(unsigned int elemento, const std::vector<unsigned int>& conjunto);

    std::vector<unsigned int> nodospadre(std::shared_ptr<NodoArbol>const &nodo);
  std::shared_ptr<NodoArbol> extraeelmejor(std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar);

};


#endif //PR1_BUSQUEDAAESTRELLA_H
