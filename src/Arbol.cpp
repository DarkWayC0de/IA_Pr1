//
// Created by darkwayc0de on 18/10/19.
//


#include "Arbol.h"

#include <utility>

Arbol::Arbol():Raiz_(nullptr) {

}

Arbol::Arbol(std::shared_ptr<NodoArbol> raiz):Raiz_(std::move(raiz)){

}

const std::shared_ptr<NodoArbol> &Arbol::GetRaiz() const {
  return Raiz_;
}
void Arbol::SetRaiz(const std::shared_ptr<NodoArbol> &raiz) {
  Raiz_ = raiz;
}


