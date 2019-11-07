#include <iostream>
#include "BusquedaAEstrella.h"


int main() {
  std::string const  CARPTETADATA = "../data/";
  std::string ficherografo;
  std::string ficheroheuristica;
  int origen,destino;
  std::cout<<"Práctica de Busqueda A* Inteligencia Artificial\n"
             "-----------------------------------------------\n"
             "Introduce el nombre del fichero del grafo(tiene que estar dentro de la carpeta data): ";
  std::cin>>ficherografo;
  std::cout<<"Introduce el nombre del fichero de heuristica(tiene que estar dentro de la carpeta data): ";;
  std::cin>>ficheroheuristica;
  BusquedaAEstrella Busqueda(CARPTETADATA+ficherografo,CARPTETADATA+ficheroheuristica);
  std::cout<<"Introduce origen de la busqueda: ";
  std::cin>>origen;
  std::cout<<"Introduce destino de la busqueda: ";
  std::cin>>destino;
  auto resultado = Busqueda.realizarBusquedaAEstrella(origen-1, destino -1);
  std::cout<<"Distancia: "<<resultado.costeminimo<<"\n"
             "Camino: ";

  for (int i = resultado.caminominimo.size()-1; i >0 ; --i) {
    std::cout<<resultado.caminominimo[i] +1<<" --> ";
  }
  std::cout<<resultado.caminominimo[0] + 1<<"\n";
  std::cout<<"Nodos generados: "<<resultado.generados<<"\n";
  std::cout<<"Nodos analizados: "<<resultado.analizados<<"\n";
  std::cout<<"Profundidad Total del arbol: "<<resultado.profundidad<<"\n";
  return 0;
}