#include "dijkstra.h"
#include <QList>

void Dijkstra::dijkstra() {
    Vertice **vertices = g->getVertice();
    Vertice *v_atual, *v_aux;
    Aresta *a;
    QList<Vertice *> f;

    for(int i=0; i < g->getVerticeCount(); i++){
        vertices[i]->setCor(Qt::white);
        vertices[i]->setPai(NULL);
        vertices[i]->setD(INF);
    }
    for(Aresta *a; a != NULL; a = a->getNext()) {
        a->setCor(Qt::black);
    }
    vertices[initial]->setCor(Qt::gray);
    emit colorChanged();
    sleep(1);
    vertices[initial] -> setD(0);
    f.append(vertices[initial]);

    while(!f.isEmpty()){
        v_atual = f.takeFirst();
        v_atual->setCor(Qt::black);
        emit colorChanged();
        sleep(1);
        for(a = v_atual->getAresta(); a != NULL; a = a->getNext()) {
            v_aux = vertices[a->getIdV2()];
            int d = v_atual->getD() + a->getW();
            if(d < v_aux->getD()){
                v_aux->setD(d);
                v_aux->setPai(v_atual);
            }
            if(v_aux->getCor() == Qt::white){
                v_aux->setCor(Qt::gray);
                emit colorChanged();
                sleep(1);
                f.append(v_aux);
            }
        }
    }
}

