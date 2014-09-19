#include <QPen>
#include "kruskal.h"
#include "aresta.h"

void Kruskal::kruskal() {
    QList<Aresta*> sortedList = sort(g->getAresta());
    Vertice *v1, *v2;

    vKruskal = new Vertice *[g->getVerticeCount()];

    for(int i=0; i < g->getVerticeCount(); i++){
        vKruskal[i] = new Vertice(i, g->getVertice()[i]->getNome(),
                                  g->getVertice()[i]->getX(),
                                  g->getVertice()[i]->getY());
        vKruskal[i]->setKruskalList(g->getVertice()[i]->getNome());
    }
    int n_a = 0;
    int i = 0;
    QPen pen;
    pen.setWidth(2);
    Aresta *a = sortedList[i++];
    while((n_a-1 < g->getVerticeCount()) && (a != NULL)) {
        pen.setColor(Qt::blue);
        a->setPen(pen);
        emit colorChanged();
        sleep(1);
        v1 = vKruskal[a->getIdV1()];
        v2 = vKruskal[a->getIdV2()];
        if(!(find(v1->getNome(), v2->getKruskalList()) ||
             find(v2->getNome(), v1->getKruskalList()))) {
            v1->add(a->getIdV1(), a->getIdV2(), a->getW());
            v1->getAresta()->setColor(Qt::red);
            v2->add(a->getIdV2(), a->getIdV1(), a->getW());
            v2->getAresta()->setColor(Qt::red);
            join(v1->getKruskalList(), v2->getKruskalList());
            n_a++;
        }
        a = sortedList[i++];
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


QList <Aresta *> Kruskal::ArestaToList(Aresta * a) {
    Aresta * h = a;
    QList <Aresta *> lista;
    while (h != NULL) {
        lista.append(h);
        h = h->getNext();
    }
    return lista;
}

QList <Aresta *> Kruskal::sort(Aresta * a) {
    QList <Aresta *> list = ArestaToList (a);
    for (int i = 0; i < list.size(); i++) {
        for (int j = i+1; j < list.size(); j++) {
            if (list[i]->getW() > list[j]->getW()) {
                list.swap(i,j);
            }
        }
    }
    return list;
}

Aresta* Kruskal::getOriginalAresta(Aresta * a){
    Vertice *v = g->getVertice()[a->getIdV1()];
    //qDebug() << v->getNome();
    Aresta * h = v->getAresta();
    //qDebug() << "origem: " << h->getIdV1();
    //qDebug() << "destino: " << a->getIdV2();
    while (h!= NULL && h->getIdV2() != a->getIdV2()){
        h = h->getNext();
    }
    return h;
    /*
    if (h != NULL && h->getIdV2() == a->getIdV2()) {
        //qDebug() << "destino h: " << h->getIdV2() << " origem h: " << h->getIdV1();
        h->setColor(Qt::red);
        emit sinal();
    }*/
}
