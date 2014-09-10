#ifndef PRIM_H
#define PRIM_H

#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"

#define INF 100000

class Prim : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial, int final) {
        this->grafo = g;
        this->initial = initial;
        this->final = final;
    }

    void run() {
        metodoPrim();
    }

    void metodoPrim();
    Vertice* popMenor();

private:
    int tempo;
    int initial;
    int final;
    Grafo *grafo;
    QList<Vertice *> lista;

signals:
    void colorChanged();

};

#endif // PRIM_H

