//
// Created by darkwayc0de on 18/10/19.
//

#ifndef PR1_NODOARBOL_H
#define PR1_NODOARBOL_H

#include <memory>
#include <vector>
class NodoArbol {
  public:
    NodoArbol();                //constructor
    ~NodoArbol() = default;     //destructor
    const std::vector<std::shared_ptr<NodoArbol>> getHijos() const;
    void setHijos(const std::vector<std::shared_ptr<NodoArbol>> &hijos);
    unsigned int getId() const;
    void setId(unsigned int id);
    double getCosteAcumulado() const;
    void setCosteAcumulado(double costeAcumulado);
    const std::shared_ptr<NodoArbol> &getPadre() const;
    void setPadre(const std::shared_ptr<NodoArbol> &padre);
    unsigned int getProfundidad() const;
    void setProfundidad(unsigned int profundidad);
    double getHeuristicaEstado() const;
    void setHeuristicaEstado(double heuristicaEstado);
  private:
    unsigned  Id_;
    double Heuristica_Estado;
    double  CosteAcumulado_;
    std::shared_ptr<NodoArbol> Padre_;
    std::vector<std::shared_ptr<NodoArbol>> Hijos_;
    unsigned Profundidad_;
};


#endif //PR1_NODOARBOL_H
