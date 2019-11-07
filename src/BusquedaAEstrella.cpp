//
// Created by darkwayc0de on 11/10/19.
//

#include <fstream>
#include <iostream>
#include <cfloat>
#include "BusquedaAEstrella.h"



BusquedaAEstrella::~BusquedaAEstrella() = default;

BusquedaAEstrella::BusquedaAEstrella(const std::string& NombreFicheroGrafo,
                                     const std::string& NombreFicheroHeuristica):
                                     Nodosgenerados_(0),
                                     Nodosanalizados_(0),
                                     Profundidad_(0),
                                     Grafo_problema_(NombreFicheroGrafo){

  this -> cargar_datos_heuristica(NombreFicheroHeuristica);

}

Resultado BusquedaAEstrella::realizarBusquedaAEstrella(unsigned origen, unsigned destino) {
  this -> Origen_ = origen;
  unsigned const noCoste = 0;
  unsigned const noProfundidad = 0;
  std::shared_ptr<NodoArbol> raiz_ = std::make_shared<NodoArbol>();
  raiz_ -> setId(origen);
  raiz_ -> setHeuristicaEstado(this -> Heuristica_Problema_[origen]);
  raiz_ -> setCosteAcumulado(noCoste);
  raiz_ -> setPadre(nullptr);
  raiz_ -> setProfundidad(noProfundidad);
  Nodosgenerados_++;
  auto parcial= analizarGenerarArbol(raiz_, destino);
  Resultado resultado;
  resultado.costeminimo =parcial.first;
  resultado.caminominimo =parcial.second;
  resultado.generados = this -> Nodosgenerados_;
  resultado.analizados= this-> Nodosanalizados_;
  resultado.profundidad= this->Profundidad_;
  this -> arbol_.SetRaiz(raiz_);
  return resultado;
}


void BusquedaAEstrella::cargar_datos_heuristica(const std::string &NombreFicheroHeuristica) {
    std::ifstream readfile(NombreFicheroHeuristica);
    if (readfile.is_open()) {
        int nodos;
        readfile >>  nodos;
        if (nodos == Grafo_problema_.getNNodos()){
            Heuristica_Problema_.resize(0);
            double valorheuristica = 0;
            readfile >> valorheuristica;
            while (!readfile.eof()){
                Heuristica_Problema_.push_back(valorheuristica);
                readfile >> valorheuristica;
            }
            if (Heuristica_Problema_.size() != nodos){
                std::cout<< "ERROR  Los datos de " << NombreFicheroHeuristica << " no son correctos, "
                                                                                 "el numero de nodos no coincide "
                                                                                 "con la cantidad de datos\n";
                exit(5);
            }
        }else{
            std::cout << "ERROR Numero de nodos de archivo "
                         "heuristica no coincide con los nodos del grafo\n";
            exit(3);
        }
        readfile.close();
    } else {
        std::cout << "ERROR en la apertura del fichero " << NombreFicheroHeuristica << "\n";
        exit(4);
    }
}

std::vector<std::shared_ptr<NodoArbol>> BusquedaAEstrella::generarHijos(const std::shared_ptr<NodoArbol>& padre,
                                                                        std::set<std::shared_ptr<NodoArbol>>& nodosAEvaluar) {
    double const noTransicion = -1.00;
    std::vector<std::shared_ptr<NodoArbol>> hijos;
    for (int i = 0; i < this -> Grafo_problema_.getNNodos(); ++i) {
        if (this -> Grafo_problema_.getTransiciones()[padre ->getId()][i] != noTransicion ){
          if (!pertenese(i , nodospadre(padre))) {
            Nodosgenerados_++;
            std::shared_ptr<NodoArbol> hijo = std::make_shared<NodoArbol>();
            hijo->setId(i);
            hijo->setHeuristicaEstado(this->Heuristica_Problema_[i]);
            hijo->setPadre(padre);
            hijo->setProfundidad(padre->getProfundidad() + 1);
            if(hijo -> getProfundidad() >Profundidad_) Profundidad_ = hijo -> getProfundidad();
            hijo->setCosteAcumulado(padre -> getCosteAcumulado()+(this->Grafo_problema_.getTransiciones()[padre->getId()][i]));
            hijos.push_back(hijo);
            nodosAEvaluar.insert(hijo);
          }
        }
    }

    return hijos;
}



std::pair<double ,std::vector<unsigned >> BusquedaAEstrella::analizarGenerarArbol(std::shared_ptr<NodoArbol> &nodo, unsigned destino) {
  auto costeMinimoActual = DBL_MAX;
  std::set<std::shared_ptr<NodoArbol>> nodosAEvaluar;
  std::vector<unsigned> camino;
  analizarGenerarArbolRecursivo(nodo, destino, costeMinimoActual,nodosAEvaluar,camino);
  std::pair<double ,std::vector<unsigned >> resultado(costeMinimoActual,camino);
  return resultado;
}

void BusquedaAEstrella::analizarGenerarArbolRecursivo(std::shared_ptr<NodoArbol> &nodo, unsigned destino,
                                                      double &costeMinimoActual,
                                                      std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar,
                                                      std::vector<unsigned> &camino) {
  Nodosanalizados_++;
  if(nodo -> getId() == destino) {
    if (costeMinimoActual > nodo->getCosteAcumulado()) {
      costeMinimoActual = nodo -> getCosteAcumulado();
      camino = nodospadre(nodo);
    }
  } else {
    nodo->setHijos(generarHijos(nodo, nodosAEvaluar));
    while (!nodosAEvaluar.empty()) {
      std::shared_ptr<NodoArbol> nodoAEvaluar = extraeelmejor(nodosAEvaluar);
      if (nodoAEvaluar->getCosteAcumulado() <= costeMinimoActual) {
        analizarGenerarArbolRecursivo(nodoAEvaluar, destino, costeMinimoActual, nodosAEvaluar, camino);
      }
    }
  }
}

bool BusquedaAEstrella::pertenese(unsigned int const elemento, std::vector<unsigned int> const& conjunto) {
    for (unsigned int i : conjunto) {
        if( i ==elemento ){
            return true;
        }
    }
    return false;
}

std::vector<unsigned> BusquedaAEstrella::nodospadre(std::shared_ptr<NodoArbol> const &nodo){
    std::vector<unsigned > camino;
    std::shared_ptr<NodoArbol> nodoanalizar=nodo;
    while(nodoanalizar->getId()!=Origen_){
        camino.push_back(nodoanalizar->getId());
        nodoanalizar =nodoanalizar -> getPadre();
    }
    camino.push_back(nodoanalizar->getId());
    return  camino;
}
std::shared_ptr<NodoArbol> BusquedaAEstrella::extraeelmejor(std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar) {
  auto mejor = nodosAEvaluar.begin();
  for (auto i = nodosAEvaluar.begin(); i != nodosAEvaluar.end() ; ++i) {
    if(((*mejor) ->getCosteAcumulado()+ (*mejor) ->getHeuristicaEstado()) >
        ((*i)->getCosteAcumulado() + (*i)->getHeuristicaEstado())){
      mejor = i;
    }
  }
  std::shared_ptr<NodoArbol> elmejornodo = *mejor;
  nodosAEvaluar.erase(mejor);
  return elmejornodo;
}
