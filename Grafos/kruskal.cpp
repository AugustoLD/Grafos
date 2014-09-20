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
        vKruskal[i]->setKruskalList(QString::number(g->getVertice()[i]->getId()));
    }
    int n_a = 0;
    int i = 0;
    while((n_a-1 < g->getVerticeCount()) && i < sortedList.size()) {
        Aresta *a = sortedList[i++];
        //qDebug() <<  g->getVertice()[a->getIdV1()]->getNome() << ' ' << g->getVertice()[a->getIdV2()]->getNome();
        a->setColor(Qt::blue);
        emit colorChanged();
        sleep(1);
        v1 = vKruskal[a->getIdV1()];
        v2 = vKruskal[a->getIdV2()];
        //qDebug() << v1->getKruskalList() << ' ' << v2->getKruskalList();
        if(!(find(v1->getId(), v2->getKruskalList()) ||
             find(v2->getId(), v1->getKruskalList()))) {
            v1->add(a->getIdV1(), a->getIdV2(), a->getW());
            v2->add(a->getIdV2(), a->getIdV1(), a->getW());
            a->setColor(Qt::red);
            emit colorChanged();
            sleep(1);
            join(v1->getKruskalList(), v2->getKruskalList());
            //qDebug() << "join: " << v1->getKruskalList() << ' ' << v2->getKruskalList();
            n_a++;
        } else {
            a->setColor(Qt::transparent);
            emit colorChanged();
            sleep(1);
        }
    }
}


bool Kruskal::find(int id, QString l) {
    QStringList s = l.split(";");
    return s.contains(QString::number(id));
}

void Kruskal::join(QString L1, QString L2) {
    qDebug() << "join: " << L1 << ' ' << L2;
    QString c = L1 + ";" +L2;
    qDebug() << c;
    QStringList S = c.split(";");
    foreach(QString str, S) {
        vKruskal[str.toInt()]->setKruskalList(c);
    }
}

/* Returns a list of each single edge, without duplications */
QList <Aresta *> Kruskal::ArestaToList(Aresta * a) {
    Aresta * h = a;
    QList <Aresta *> list;
    bool duplicated;
    while (h != NULL) {
        duplicated = false;
        for(int i = 0; i < list.size(); i++) {
            if(h->getIdV1() == list[i]->getIdV2() &&
                h->getIdV2() == list[i]->getIdV1()) {
                duplicated = true;
                h->setColor(Qt::transparent);
                break;
            }
        }
        if(!duplicated) {
            list.append(h);
            qDebug() << g->getVertice()[h->getIdV1()]->getNome() << ' ' << g->getVertice()[h->getIdV2()]->getNome();
        }
        h = h->getNext();
    }
    emit colorChanged();
    return list;
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
    qDebug() << "=====================";
    for(int i = 0; i < list.size(); i++){
        qDebug() << g->getVertice()[list[i]->getIdV1()]->getNome() << ' ' << g->getVertice()[list[i]->getIdV2()]->getNome();
    }
    return list;
}
