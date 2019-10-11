//
// Created by darkwayc0de on 11/10/19.
//

#include <fstream>
#include <iostream>
#include "BusquedaAEstrella.h"

BusquedaAEstrella::~BusquedaAEstrella() = default;

BusquedaAEstrella::BusquedaAEstrella(const std::string& NombreFicheroGrafo,
                                     const std::string& NombreFicheroHeuristica) :
Grafo_problema_(NombreFicheroGrafo){

  this -> Cargar_datos_heuristica(NombreFicheroHeuristica);

}

void BusquedaAEstrella::Cargar_datos_heuristica(const std::string &NombreFicheroHeuristica) {
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
        std::cout << "EROR en la apertura del fichero " << NombreFicheroHeuristica << "\n";
        exit(4);
    }
}
