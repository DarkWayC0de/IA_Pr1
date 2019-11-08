//
// Created by darkwayc0de on 18/10/19.
//

#ifndef PR1_ARBOL_H
#define PR1_ARBOL_H


#include "NodoArbol.h"

class Arbol {
 public:
    Arbol();
    explicit Arbol(std::shared_ptr<NodoArbol> raiz);
    ~Arbol()= default;
  const std::shared_ptr<NodoArbol> &GetRaiz() const;
  void SetRaiz(const std::shared_ptr<NodoArbol> &raiz);

 private:
    std::shared_ptr<NodoArbol> Raiz_;
};


#endif //PR1_ARBOL_H
