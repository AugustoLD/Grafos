#include "prim.h"

void Prim::prim() {
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
        emit colorChanged();
        sleep(1);
    }
    for(int i = 0; i < n; i++) {
        V[i]->setCor(Qt::white);
        if(V[i]->getPai() != NULL) {
            qDebug() << V[i]->getNome() << ' ' << V[i]->getPai()->getNome();
            Vertice *v_aux = V[i]->getPai();
            Aresta *a_aux = grafo->getAresta();
            while(a_aux != NULL) {
                if((a_aux->getIdV1() == V[i]->getId() && a_aux->getIdV2() == v_aux->getId()) ||
                   (a_aux->getIdV2() == V[i]->getId() && a_aux->getIdV1() == v_aux->getId())) {
                    a_aux->setColor(Qt::red);
                }
                a_aux = a_aux->getNext();
            }
        }
    }
    Aresta *a_aux = grafo->getAresta();
    while(a_aux != NULL) {
        if(a_aux->getColor() != Qt::red) {
            a_aux->setColor(Qt::transparent);
        }
        a_aux = a_aux->getNext();
    }
    emit colorChanged();
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
