#include <iostream>
#include <fstream>
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

    ficherografo = "Grafo";
    ficheroheuristica = "heuristica_O1F5";
    origen =1;
    destino =5;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "Grafo1";
    ficheroheuristica = "Grafo1Heuristica";
    origen =1;
    destino =8;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "Grafo1";
    ficheroheuristica = "Grafo1Heuristica2";
    origen =1;
    destino =8;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "Grafo2.txt";
    ficheroheuristica = "Grafo2Heuristica1.txt";
    origen =2;
    destino =14;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    ficherografo = "Grafo2.txt";
    ficheroheuristica = "Grafo2Heuristica2.txt";
    origen =2;
    destino =14;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);;
    writefile<<"---------------------------------------------\n";
    ficherografo = "Grafo3.txt";
    ficheroheuristica = "Grafo3Heuristica1.txt";
    origen =1;
    destino =15;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    ficherografo = "Grafo3.txt";
    ficheroheuristica = "Grafo3Heuristica2.txt";
    origen =1;
    destino =15;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);;
    writefile<<"---------------------------------------------\n";
    ficherografo = "Grafo4.txt";
    ficheroheuristica = "Grafo4Heuristica1.txt";
    origen =10;
    destino =18;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    ficherografo = "Grafo4.txt";
    ficheroheuristica = "Grafo4Heuristica2.txt";
    origen =10;
    destino =18;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
    writefile<<"---------------------------------------------\n";
    ficherografo = "GrafoRumania.txt";
    ficheroheuristica = "GrafoRumaniaHeuristica.txt";
    origen =1;
    destino =2;
    imprime(writefile,ficherografo,ficheroheuristica,origen,destino);
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
  auto resultado = Busqueda.realizarBusquedaAEstrella(origen - 1, destino - 1);
  writefile << "Distancia: " << resultado.costeminimo << "\n"
                                                         "Camino: ";

  for (int i = resultado.caminominimo.size() - 1; i > 0; --i) {
    writefile << resultado.caminominimo[i] + 1 << " --> ";
  }
  writefile << resultado.caminominimo[0] + 1 << "\n";
  writefile << "Nodos generados: " << resultado.generados << "\n";
  writefile << "Nodos analizados: " << resultado.analizados << "\n";
  writefile << "Profundidad Total del arbol: " << resultado.profundidad << "\n";

}
