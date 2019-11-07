//
// Created by darkwayc0de on 4/10/19.
//

#include "Grafo.h"
#include <fstream>
#include <iostream>


Grafo::Grafo(const std::string& nombrefichero) {
    std::ifstream readfile(nombrefichero);
    if ( readfile.is_open() ){
        readfile >>N_nodos_;
        Reseptor_transiciones(readfile);
        readfile.close();
    }else {
        std::cout<<"ERROR en la apertura del fichero "<<nombrefichero<<"\n";
        exit(1);
    }
}

void Grafo::Reseptor_transiciones(std::ifstream &is) {
    if (this->N_nodos_> 0){
        Transiciones_.resize(this->N_nodos_);
        for (int i = 0; i <this->N_nodos_; ++i) {
            Transiciones_[i].resize(this->N_nodos_);
            for (int j = 0; j < this->N_nodos_; ++j) {
                Transiciones_[i][j] = -2;
            }
            Transiciones_[i][i] = 0;
        }
        double entrada = 0;
        while(!is.eof()){
            is >> entrada;
            bool introducido =false;
            for (int i = 0; i < this -> N_nodos_ && !introducido; ++i) {
                for (int j = 0; j <this -> N_nodos_ && !introducido ; ++j) {
                    if (Transiciones_[i][j] == -2){
                        Rellenar_transiciones(i,j,entrada);
                        introducido=true;
                    }
                }
            }
        }
    } else {
        std::cout<<"Se han intentado generar transiciones sin numero de nodos\n";
        exit( 2);
    }
}

inline void Grafo::Rellenar_transiciones(int i, int j, double data){
Transiciones_[i][j] = data;
Transiciones_ [j][i] = data;
}

int Grafo::getNNodos() const {
    return N_nodos_;
}

const std::vector<std::vector<double>> &Grafo::getTransiciones() const {
    return Transiciones_;
}

void Grafo::setTransiciones(const std::vector<std::vector<double>> &transiciones) {
    Transiciones_ = transiciones;
}
