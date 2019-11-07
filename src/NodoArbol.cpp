//
// Created by darkwayc0de on 18/10/19.
//

#include "NodoArbol.h"

NodoArbol::NodoArbol() = default;

const std::vector<std::shared_ptr<NodoArbol>> NodoArbol::getHijos() const {
    return Hijos_;
}

void NodoArbol::setHijos(const std::vector<std::shared_ptr<NodoArbol>> &hijos) {
    Hijos_ = hijos;
}

unsigned int NodoArbol::getId() const {
    return Id_;
}

void NodoArbol::setId(unsigned int id) {
    Id_ = id;
}

double NodoArbol::getCosteAcumulado() const {
    return CosteAcumulado_;
}

void NodoArbol::setCosteAcumulado(double costeAcumulado) {
    CosteAcumulado_ = costeAcumulado;
}

const std::shared_ptr<NodoArbol> &NodoArbol::getPadre() const {
    return Padre_;
}

void NodoArbol::setPadre(const std::shared_ptr<NodoArbol> &padre) {
    Padre_ = padre;
}

unsigned int NodoArbol::getProfundidad() const {
    return Profundidad_;
}

void NodoArbol::setProfundidad(unsigned int profundidad) {
    Profundidad_ = profundidad;
}

double NodoArbol::getHeuristicaEstado() const {
    return Heuristica_Estado;
}

void NodoArbol::setHeuristicaEstado(double heuristicaEstado) {
    Heuristica_Estado = heuristicaEstado;
}



