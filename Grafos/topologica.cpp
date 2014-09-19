#include "topologica.h"

void Topologica::ordenacaoTopologica() {
    Vertice **V = grafo->getVertice();
    int n = grafo->getVerticeCount();
    for(int i = 0; i < n; i++) {
        V[i]->setPai(NULL);
        V[i]->setTi(-1);
        V[i]->setTo(-1);
        V[i]->setCor(Qt::white);
    }
    for(Aresta *a; a != NULL; a = a->getNext()) {
        a->setCor(Qt::black);
    }
    tempo = 0;
    for(int i = initial; i < n; i++) {
        if(V[i]->getCor() == Qt::white) {
            visit(V[i]);
        }
    }
}

void Topologica::visit(Vertice *v) {
    Aresta *a; Vertice *va;
    v->setCor(Qt::gray);
    emit colorChanged();
    sleep(1);
    v->setTi(tempo++);
    for(a = v->getAresta(); a != NULL; a = a->getNext()) {
        va = grafo->getVertice()[a->getIdV2()];
        if(va->getCor() == Qt::white) {
            va->setPai(v);
            visit(va);
        }
    }
    v->setTo(tempo++);
    v->setCor(Qt::black);
    lista.append(v);
    emit colorChanged();
    sleep(1);
}
