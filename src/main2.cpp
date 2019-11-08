#include <iostream>
#include <fstream>
#include <cfloat>
#include "BusquedaAEstrella.h"

void imprime(std::ostream &writefile, const std::string& ficherografo, const std::string& ficheroheuristica, int origen, int destino);
int main() {
  std::ofstream writefile("../out.txt");
  if(writefile.is_open()) {

    std::string ficherografo;
    std::string ficheroheuristica;
    int origen, destino;
    writefile << "Práctica de Busqueda A* Inteligencia Artificial\n"
                 "-----------------------------------------------\n";

    ficherografo = "GrafoCorrec1.txt";
    ficheroheuristica = "GrafoCorrec1Heur.txt";
    origen =1;
    destino =8;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "GrafoCorrec2.txt";
    ficheroheuristica = "GrafoCorrec2Heur.txt";
    origen =2;
    destino =14;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "GrafoCorrec3.txt";
    ficheroheuristica = "GrafoCorrec3Heur.txt";
    origen =1;
    destino =15;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "GrafoCorrec4.txt";
    ficheroheuristica = "GrafoCorrec4Heur.txt";
    origen =10;
    destino =18;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    writefile.close();
    return 0;
  } else{
    return 43;
  }
}
void imprime(std::ostream &writefile,
             const std::string& ficherografo,
             const std::string& ficheroheuristica,
             int origen,
             int destino) {
  std::string const CARPTETADATA = "../data/";
  writefile << "Fichero del grafo: "<<ficherografo<<"\n";

  writefile << "Fichero de heuristica: "<<ficheroheuristica<<"\n";

  BusquedaAEstrella Busqueda(CARPTETADATA + ficherografo, CARPTETADATA + ficheroheuristica);
  writefile << "Origen: "<<origen<<"\n";
  writefile << "Destino: "<<destino<<"\n";
  auto resultado = Busqueda.realizarBusquedaAEstrellaModificacion(origen - 1, destino - 1); //TODO Se cambio el metodo para la modificacion
  writefile << "Distancia: " ;
  if (resultado.costeminimo ==DBL_MAX){
    writefile<<" Fallo\n";
  }else {
    writefile << resultado.costeminimo << "\n"
                                          "Camino: ";
    for (int i = resultado.caminominimo.size() - 1; i > 0; --i) {
      writefile << resultado.caminominimo[i] + 1 << " --> ";
    }
    writefile << resultado.caminominimo[0] + 1 << "\n";
  }
  writefile << "Nodos generados: " << resultado.generados << "\n";
  writefile << "Nodos analizados: " << resultado.analizados << "\n";
  writefile << "Profundidad Total del arbol: " << resultado.profundidad << "\n";

}
