//
// Created by darkwayc0de on 11/10/19.
//

#include <fstream>
#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <time.h>
#include "BusquedaAEstrella.h"



BusquedaAEstrella::~BusquedaAEstrella() = default;
/**
 * @brief Constructor de BusquedaAEstrella
 *
 * @param NombreFicheroGrafo
 * @param NombreFicheroHeuristica
 */
BusquedaAEstrella::BusquedaAEstrella(const std::string& NombreFicheroGrafo,
                                     const std::string& NombreFicheroHeuristica):
                                     Nodosgenerados_(0),
                                     Nodosanalizados_(0),
                                     Profundidad_(0),
                                     Grafo_problema_(NombreFicheroGrafo){
  this -> cargar_datos_heuristica(NombreFicheroHeuristica);   //carga datos de la heuristica
}
/**
 * @brief Empieza a realizar la busqueda estrella
 *
 *   Crea la raiz del arbol llama elmetodo que realizalos analisi i generacionespertinentes
 *   y devuelve los resultados en una estructura Resultados
 *
 * @param origen  defiene origen de la busqueda
 * @param destino define destino de la busqueda
 * @return  devuelve una estructura resultado con todos los datos de la buqueda
 */
Resultado BusquedaAEstrella::realizarBusquedaAEstrella(unsigned origen, unsigned destino) {
  this -> Origen_ = origen;
  unsigned const noCoste = 0;
  unsigned const noProfundidad = 0;
  std::shared_ptr<NodoArbol> raiz_ = std::make_shared<NodoArbol>();
  raiz_ -> setId(origen);
  raiz_ -> setHeuristicaEstado(this -> Heuristica_Problema_[origen]);
  raiz_ -> setCosteAcumulado(noCoste);
  raiz_ -> setPadre(nullptr);
  raiz_ -> setProfundidad(noProfundidad);
  Nodosgenerados_++;
  auto parcial= analizarGenerarArbol(raiz_, destino);
  Resultado resultado;
  resultado.costeminimo =parcial.first;
  resultado.caminominimo =parcial.second;
  resultado.generados = this -> Nodosgenerados_;
  resultado.analizados= this-> Nodosanalizados_;
  resultado.profundidad= this->Profundidad_;
  this -> arbol_.SetRaiz(raiz_);
  return resultado;
}
/**
 * @brief Carga los datos de la heuristica en el atrivuto petinente de la clase
 *
 * @param NombreFicheroHeuristica
 */

void BusquedaAEstrella::cargar_datos_heuristica(const std::string &NombreFicheroHeuristica) {
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
      std::cout << "ERROR en la apertura del fichero " << NombreFicheroHeuristica << "\n";
      exit(4);
  }
}
/**
 * @brief Dado un padre genera todos los hijos controlando que no esten en su rama del arbol
 *
 * @param padre   nodo apartir del cul se generaran sus hijos
 * @param nodosAEvaluar   estructura que guarda los nodos para su posterior evaluacion
 * @return  devuelve los hijos generados
 */

std::vector<std::shared_ptr<NodoArbol>> BusquedaAEstrella::generarHijos(const std::shared_ptr<NodoArbol>& padre,
                                                                        std::set<std::shared_ptr<NodoArbol>>& nodosAEvaluar) {
  double const noTransicion = -1.00;
  std::vector<std::shared_ptr<NodoArbol>> hijos;
  for (int i = 0; i < this -> Grafo_problema_.getNNodos(); ++i) {
    if (this -> Grafo_problema_.getTransiciones()[padre ->getId()][i] != noTransicion ){
      if (!pertenece(i , nodospadre(padre))) {
        Nodosgenerados_++;
        std::shared_ptr<NodoArbol> hijo = std::make_shared<NodoArbol>();
        hijo->setId(i);
        hijo->setHeuristicaEstado(this->Heuristica_Problema_[i]);
        hijo->setPadre(padre);
        hijo->setProfundidad(padre->getProfundidad() + 1);
        if(hijo -> getProfundidad() >Profundidad_){
          Profundidad_ = hijo -> getProfundidad();
        }
        hijo->setCosteAcumulado(padre -> getCosteAcumulado()+(this->Grafo_problema_.getTransiciones()[padre->getId()][i]));
        hijos.push_back(hijo);
        nodosAEvaluar.insert(hijo);
      }
    }
  }
  return hijos;
}

/**
 * @brief Inicialisa los valores resultantes de la busqueda
 *
 *
 * @param raiz  recibe la raiz para realizar la buque
 * @param destino  recibe el destino de la busqueda
 * @return devuelve una estructura pair con el coste minimo y el camino encontrado
 */
std::pair<double ,std::vector<unsigned >> BusquedaAEstrella::analizarGenerarArbol(std::shared_ptr<NodoArbol> &raiz, unsigned destino) {
  auto costeMinimoActual = DBL_MAX;
  std::set<std::shared_ptr<NodoArbol>> nodosAEvaluar; //estructura de datos que guardara los nodos pendientes a analizar
  std::vector<unsigned> camino;
  analizarGenerarArbolRecursivo(raiz, destino, costeMinimoActual, nodosAEvaluar, camino);
  std::pair<double ,std::vector<unsigned >> resultado(costeMinimoActual,camino);
  return resultado;
}
/**
 * @brief  Recursivamente realizala busqueda a estrella
 *   Recursivamente analiza si el nodo actual es el final encaso afirmativo revisa si es
 *   mejor opcion que alguna que se pudiera haber encontrado anteriormente  para si fuese así guardarla como resultado
 *   En caso de que el nodo actual no fuera el final, genera ss hijos y extrae el sigiente no a analizar
 *   mediante recursividad
 *
 * @param nodo
 * @param destino
 * @param costeMinimoActual
 * @param nodosAEvaluar
 * @param camino
 */
void BusquedaAEstrella::analizarGenerarArbolRecursivo(std::shared_ptr<NodoArbol> &nodo, unsigned destino,
                                                      double &costeMinimoActual,
                                                      std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar,
                                                      std::vector<unsigned> &camino) {
  Nodosanalizados_++;
  if(nodo -> getId() == destino) {
    if (costeMinimoActual > nodo->getCosteAcumulado()) {
      costeMinimoActual = nodo -> getCosteAcumulado();
      camino = nodospadre(nodo);
    }
  } else {
    nodo->setHijos(generarHijos(nodo, nodosAEvaluar));
    while (!nodosAEvaluar.empty()) {
      std::shared_ptr<NodoArbol> nodoAEvaluar = extraeelmejor(nodosAEvaluar);
      if (nodoAEvaluar->getCosteAcumulado() <= costeMinimoActual) {
        analizarGenerarArbolRecursivo(nodoAEvaluar, destino, costeMinimoActual, nodosAEvaluar, camino);
      }
    }
  }
}

/**
 * @brief Comprube que un elementopertenece a un conjunto
 * @param elemento
 * @param conjunto
 * @return  devuelve un verdaddero o falso
 */

bool BusquedaAEstrella::pertenece(unsigned int const elemento, std::vector<unsigned int> const& conjunto) {
  for (unsigned int i : conjunto) {
    if( i ==elemento ){
      return true;
    }
  }
  return false;
}

/**
 * @brief Apartir de un nodo busca los padres hasta la raiz
 * @param nodo  apartir del cual se revisaran los padres
 * @return  devuelve un vector con los nombres de los padres
 */
std::vector<unsigned> BusquedaAEstrella::nodospadre(std::shared_ptr<NodoArbol> const &nodo){
  std::vector<unsigned > camino;
  std::shared_ptr<NodoArbol> nodoanalizar=nodo;
  while(nodoanalizar->getId()!=Origen_){
    camino.push_back(nodoanalizar->getId());
    nodoanalizar =nodoanalizar -> getPadre();
  }
  camino.push_back(nodoanalizar->getId());
  return  camino;
}
/**
 * @brief Extra de la extructura de datos el nodo con menor costeacumulado + la heuristica siendo este el mejor para continuar la busqueda
 * @param nodosAEvaluar  estructura de nodos que faltan por prosesar
 * @return  devuelve el nodo a analizar
 */
std::shared_ptr<NodoArbol> BusquedaAEstrella::extraeelmejor(std::set<std::shared_ptr<NodoArbol>> &nodosAEvaluar) {
  auto mejor = nodosAEvaluar.begin();
  for (auto i = nodosAEvaluar.begin(); i != nodosAEvaluar.end() ; ++i) {
    if(((*mejor) ->getCosteAcumulado() + (*mejor) ->getHeuristicaEstado()) >
        ((*i)->getCosteAcumulado() + (*i)->getHeuristicaEstado())){
      mejor = i;
    }
  }
  std::shared_ptr<NodoArbol> elmejornodo = *mejor;
  nodosAEvaluar.erase(mejor);
  return elmejornodo;
}
Resultado BusquedaAEstrella::realizarBusquedaAEstrellaModificacion(unsigned origen, unsigned destino) { //TODO Modificacion
  std::srand(time(NULL));                                                //arancamos el generador de aleatorios
  this -> Origen_ = origen;
  unsigned const noCoste = 0;
  unsigned const noProfundidad = 0;
  std::shared_ptr<NodoArbol> raiz_ = std::make_shared<NodoArbol>();
  raiz_ -> setId(origen);
  raiz_ -> setHeuristicaEstado(this -> Heuristica_Problema_[origen]);  //inicializamos raiz 229-237
  raiz_ -> setCosteAcumulado(noCoste);
  raiz_ -> setPadre(nullptr);
  raiz_ -> setProfundidad(noProfundidad);
  Nodosgenerados_++;                                                          //contamos la raiz como generado
  auto costeMinimoActual = DBL_MAX;                           //creamos variables para el minimo de las 10 veces
  std::vector<unsigned> caminofinal;
  for (int i = 0; i <11 ; ++i) {                              //realiza las 10 repeticiones
    auto costeMinimoPorbusqueda = DBL_MAX;                    //coste minimo de esta buqueda
    std::set<std::shared_ptr<NodoArbol>> nodosAEvaluar;       //estructura de datos que guardara entre los nodos a escoger
    std::vector<unsigned> camino;
    raiz_->setHijos(generarHijos(raiz_, nodosAEvaluar));    //generamos los hijos de la raiz
    int numero_aleatorio = rand() % nodosAEvaluar.size();             //entre las posibilidades de nodos elejimos uno
    for (auto k = nodosAEvaluar.begin(); k != nodosAEvaluar.end(); ++k) {
      if (numero_aleatorio == 0) {          //entramos a la posivildad elegida con aleatorio
        analisisrecursivo(*k, destino, costeMinimoPorbusqueda, camino);
      }
      numero_aleatorio--;
    }
    if(costeMinimoActual>costeMinimoPorbusqueda){  //tras realizar la busqueda comprobamos que el camino obtenido sea mejor
      costeMinimoActual=costeMinimoPorbusqueda;    //que otro posible que ya puderamos tener en caso afirmativo lo guardamos
      caminofinal =camino;
    }
  }
  Resultado resultado;                                //guardamos los datos y devolvemos valores linea 258-265
  resultado.costeminimo = costeMinimoActual;
  resultado.caminominimo =caminofinal;
  resultado.generados = this -> Nodosgenerados_;
  resultado.analizados= this-> Nodosanalizados_;
  resultado.profundidad= this->Profundidad_;
  this -> arbol_.SetRaiz(raiz_);
  return resultado;
}

void BusquedaAEstrella::analisisrecursivo(const std::shared_ptr<NodoArbol> &nodo,
                                          unsigned int destino,
                                          double &coste,
                                          std::vector<unsigned int>& camino) {   //TODO Funcion nueva modificacion
  Nodosanalizados_++;   //sumamos uno a analizados
  if (nodo->getId() ==destino){     //si es el destino guardamos  su coste y camino
    coste = nodo -> getCosteAcumulado();
    camino = nodospadre(nodo);
  }else{                                      //en caso contrario
    std::set<std::shared_ptr<NodoArbol>> nodosAEvaluar; //estructura para guaradar la posibilidades de continucion
    nodo->setHijos(generarHijos(nodo, nodosAEvaluar));  //generamos las posibles continuaciones
    if (!nodosAEvaluar.empty()) {                                //si no existen continuciones terminamos y en caso de que si existan
      std::shared_ptr<NodoArbol> nodoAEvaluar = extraeelmejor(nodosAEvaluar);   //extraemos la mejor segun coste+ heuristica
      analisisrecursivo(nodoAEvaluar,destino,coste,camino);    //analizamos recursivamente la mejor extraida
    }
  }
}
