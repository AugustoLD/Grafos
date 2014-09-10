#include "kruskal.h"
#include "aresta.h"

void Kruskal::kruskal() {
    Aresta *a = g->getAresta();
    Vertice *v1, *v2;
    vKruskal = new Vertice *[g->getVerticeCount()];

    for(int i=0; i < g->getVerticeCount(); i++){
        vKruskal[i] = new Vertice(i, g->getVertice()[i]->getNome(),
                                  g->getVertice()[i]->getX(),
                                  g->getVertice()[i]->getY());
    }

    int n_a = 0;
    while((n_a-1 < g->getVerticeCount()) && (a != NULL)){
        v1 = vKruskal[a->getIdV1()];
        v2 = vKruskal[a->getIdV2()];
        //if(!find(v1,v2)) {
            //v1->add(a->getIdV1(), a->getIdV2(), a->getW());
            //v2->add(a->getIdV2(), a->getIdV1(), a->getW());
            //join(v1,v2); //usa split se usar string, lista...
            //n_a++;
        //}
        a = a->getNext();
    }
}
/*
bool Kruskal::find(QString nome, QString L) {
    QStringList S = split();
    return S.contain(nome);
}

bool Kruskal::join(QString L1, QString L2){
    QString c = L1 + L2;
    QStringList S = c.split();
    for each S
        atualiza c;
}
*/
