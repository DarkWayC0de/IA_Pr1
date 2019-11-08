//
// Created by darkwayc0de on 11/10/19.
//

#ifndef PR1_BUSQUEDAAESTRELLA_H
#define PR1_BUSQUEDAAESTRELLA_H

#include <set>
#include "Grafo.h"
#include "NodoArbol.h"
#include "Arbol.h"
struct Resultado{  //Estructura encapsuladora de resultados  de la buqueda
  double costeminimo;
  std::vector<unsigned> caminominimo;
  unsigned generados;
  unsigned analizados;
  unsigned profundidad;
};

class BusquedaAEstrella {
 public:
    BusquedaAEstrella(const std::string& NombreFicheroGrafo, const std::string& NombreFicheroHeuristica);
    ~BusquedaAEstrella();
     Resultado realizarBusquedaAEstrella(unsigned origen, unsigned destino);
     Resultado realizarBusquedaAEstrellaModificacion(unsigned int origen, unsigned int destino);//TODO se creo para la modficacion
 private:
    Grafo Grafo_problema_;
    std::vector<double> Heuristica_Problema_;
    unsigned Nodosgenerados_;
    unsigned Nodosanalizados_;
    unsigned Profundidad_;
    unsigned Origen_;
    Arbol arbol_;
    void cargar_datos_heuristica(const std::string& NombreFicheroHeuristica);
    std::vector<std::shared_ptr<NodoArbol>> generarHijos(const std::shared_ptr<NodoArbol>& padre,
                                                         std::set<std::shared_ptr<NodoArbol>>& nodosAEvaluar);
    std::pair<double ,std::vector<unsigned >> analizarGenerarArbol(std::shared_ptr<NodoArbol> &raiz,
                                                                    unsigned destino);
    void  analizarGenerarArbolRecursivo(std::shared_ptr<NodoArbol> &nodo,
                                        unsigned destino,
                                        double &costeMinimoActual,
                                        std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar,
                                        std::vector<unsigned >& camino);
    bool pertenece(unsigned int elemento, const std::vector<unsigned int>& conjunto);

    std::vector<unsigned int> nodospadre(std::shared_ptr<NodoArbol>const &nodo);
    std::shared_ptr<NodoArbol> extraeelmejor(std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar);

  void analisisrecursivo(const std::shared_ptr<NodoArbol> &nodo,
                         unsigned int destino,
                         double &coste,
                         std::vector<unsigned int> &camino); //TODO Funcion nueva modificacion
};



#endif //PR1_BUSQUEDAAESTRELLA_H
