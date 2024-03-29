//
// Created by darkwayc0de on 4/10/19.
//

#ifndef PR1_GRAFO_H
#define PR1_GRAFO_H


#include <vector>
#include <string>


class Grafo {
  public:
    explicit Grafo(const std::string& nombrefichero);
    virtual ~Grafo()= default;
    int getNNodos() const;
    const std::vector<std::vector<double>> &getTransiciones() const;
    void setTransiciones(const std::vector<std::vector<double>> &transiciones);
  private:
    int N_nodos_;  // Numero de nodos del grafo
    std::vector<std::vector<double>> Transiciones_;
    void Receptor_transiciones(std::ifstream &is);
    void Rellenar_transiciones(int i, int j, double data);
};


#endif //PR1_GRAFO_H
