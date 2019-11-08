//
// Created by darkwayc0de on 4/10/19.
//

#include "Grafo.h"
#include <fstream>
#include <iostream>
/**
 * @brief Constructor  resive el nombre de un archivo del grafo y su correcta apertura
 *  recoge el tamaño del grafo y le envia el resto del archivo a Receptor_transiciones
 *  tras la vuelta cierra el archivo
 * @param Grafo.ccp
 */

Grafo::Grafo(const std::string& nombrefichero) {
  std::ifstream readfile(nombrefichero);
  if ( readfile.is_open() ){
    readfile >>N_nodos_;
    Receptor_transiciones(readfile);
    readfile.close();
  }else {
    std::cout<<"ERROR en la apertura del fichero "<<nombrefichero<<"\n";
    exit(1);
  }
}
/**
 * @brief Apartir del archivo rellena las transiciones
 *
 * @param is archivo de entrada
 */
void Grafo::Receptor_transiciones(std::ifstream &is) {
  if (this->N_nodos_> 0){
    Transiciones_.resize(this->N_nodos_);
    for (int i = 0; i <this->N_nodos_; ++i) {          //Se inicializa la matriz de transiciones
      Transiciones_[i].resize(this->N_nodos_);// lineas 33-40
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
            Rellenar_transiciones(i,j,entrada);         //se establece el camino del nodo uno al dos
            introducido=true;  //sale de los bucles     // y del dos al uno con el mismo valor
          }
        }
      }
    }
  } else {
    std::cout<<"Se han intentado generar transiciones sin numero de nodos\n";
    exit( 2);
  }
}
/**
 * @brief Rellena las transiciones de forma cimetrica
 *
 * @param i  primera cordenada de la matriz
 * @param j  segunda cordenada de la matriz
 * @param data   dato a guardar
 */
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
