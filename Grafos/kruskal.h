#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"

class Kruskal : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial) {
        this->g = g;
        this->initial = initial;
    }

    void run() {
        kruskal();
    }

private:
    int tempo;
    int initial;
    Grafo *g;
    Vertice **vKruskal;
    void kruskal();
    bool find(QString nome, QString l);
    void join(QString L1, QString L2);
    QList <Aresta *> ArestaToList (Aresta * a);
    QList <Aresta *> sort(Aresta * a);
    Aresta* getOriginalAresta(Aresta * a);

signals:
    void colorChanged();

};

#endif // KRUSKAL_H
