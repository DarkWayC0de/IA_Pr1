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

private:
    int N_nodos_{};
    std::vector<std::vector<double>> Transiciones_;
    void Reseptor_transiciones(std::ifstream &is);

    void Rellenar_transiciones(int i, int j, double data);
};


#endif //PR1_GRAFO_H
