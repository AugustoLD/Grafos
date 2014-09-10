#include "prim.h"

void Prim::metodoPrim() {
    qDebug() << "chegou metodo PRIM";
    int n = grafo->getVerticeCount();
    Vertice **V = grafo->getVertice();
    Vertice *verticeAtual, *vertice;
    Aresta *aresta;
    for( int i = 0; i < n; i++ ) {
        V[i]->setD(INF);
        V[i]->setPai(NULL);
        V[i]->setCor(Qt::white);
        lista.append(V[i]);
    }
    qDebug() << "Saiu do for";
    V[initial]->setD(0);
    while ( !lista.empty() ) {
        qDebug() << "ListaSize:" << lista.size();
        vertice = popMenor();
        qDebug() << "ListaSizeDepois:" << lista.size();
        vertice->setCor(Qt::gray);
        emit colorChanged();
        sleep(1);
        for ( aresta = vertice->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
            verticeAtual = V[aresta->getIdV2()];
            if ( (verticeAtual->getCor() != Qt::black ) && (verticeAtual->getD() > aresta->getW()) ) {
                verticeAtual->setPai(vertice);
                verticeAtual->setD(aresta->getW());
            }
        }
        vertice->setCor(Qt::black);
        qDebug() << "Pintou Preto ";
        emit colorChanged();
        sleep(1);
    }
}

Vertice* Prim::popMenor() {
    int menor = 0;
    for (int i= 1; i < lista.size(); i++ ) {
        if ( lista.at(i)->getD() < lista.at(menor)->getD() ) {
            menor = i;
        }
    }
    qDebug() << "Menor: " << lista.at(menor)->getNome() << "Com distancia: " << lista.at(menor)->getD();
    return lista.takeAt(menor);
}
