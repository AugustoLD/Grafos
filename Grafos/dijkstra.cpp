#include "dijkstra.h"
/*
void Dijkstra :: dijkstra (int Vi){
    Vertice *V, *Va;
    Aresta *a;
    Lista *L = new Lista();

    for(int i=0; i<size; i++){
        Vertice[i] -> setColor(Qt::white);
        Vertice[i] -> setPai(null);
        Vertice[i] -> setD(INF);
    }
    Vertice[Vi] -> setColor(Qt::gray);
    Vertice[Vi] -> setD(0);
    L->append(Vertice[Vi]);
    while(!L->isEmpty()){
        V = L->removeMenorVertice();
        V = setColor(Qt::black);
    }
    for(a = V->getAresta(); a != NULL; a = a->getNext()){
        Va = Vertice[a->getV2()];
        int d = V->getD() + a->getW();
        if( d < Va->getD){
            Va->setD(d);
            Va->setPai(v);
        }
    }
    if(Va->getColor != Qt::white){
        Va->setColor(Qt::gray);
        L->append(Va);
    }
    delete L;
}*/

