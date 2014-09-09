#include "depthfirstsearch.h"
#include <iostream>


void DepthFirstSearch::dfs() {
    Vertice **V = g->getVertice();
    int n = g->getVerticeCount();

    for(int i = 0; i < n; i++) {
        V[i]->setPai(NULL);
        V[i]->setTi(-1);
        V[i]->setTo(-1);
        V[i]->setCor(Qt::white);
    }
    tempo = 0;
    for(int i = initial; i < n; i++) {
        if(V[i]->getCor() == Qt::white) {
            visit(V[i]);
        }
    }
}

void DepthFirstSearch::visit(Vertice *v) {
    Aresta *a; Vertice *va;
    v->setCor(Qt::gray);
    emit colorChanged();
    sleep(1);
    v->setTi(tempo++);
    for(a = v->getAresta(); a != NULL; a = a->getNext()) {
        va = g->getVertice()[a->getIdV2()];
        std::cout << v->getNome().toStdString() << ' ' << va->getNome().toStdString() << std::endl;

        if(va->getCor() == Qt::white) {
            va->setPai(v);
            visit(va);
        }
    }
    v->setTo(tempo++);
    v->setCor(Qt::black);
    emit colorChanged();
    sleep(1);
}
