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
        vKruskal[i]->setKruskalList(QString::number(g->getVertice()[i]->getId()));
    }
    for(Aresta *a; a != NULL; a = a->getNext()) {
        a->setCor(Qt::black);
    }

    int n_a = 0;
    while((n_a-1 < g->getVerticeCount()) && (a != NULL)) {
        v1 = vKruskal[a->getIdV1()];
        v2 = vKruskal[a->getIdV2()];
        if(!(find(v1->getNome(), v2->getKruskalList()) ||
              find(v2->getNome(), v1->getKruskalList()))) {
            v1->add(a->getIdV1(), a->getIdV2(), a->getW());
            v1->getAresta()->setCor(Qt::red);
            v2->add(a->getIdV2(), a->getIdV1(), a->getW());
            v2->getAresta()->setCor(Qt::red);
            join(v1->getKruskalList(), v2->getKruskalList());
            n_a++;
        }
        a = a->getNext();
    }
}


bool Kruskal::find(QString nome, QString l) {
    QStringList s = l.split(";");
    return s.contains(nome);
}

void Kruskal::join(QString L1, QString L2) {
    QString c = L1 + ";" +L2;
    QStringList S = c.split(";");
    foreach(QString str, S) {
         vKruskal[str.toInt()]->setKruskalList(c);
    }
}
