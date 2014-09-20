#ifndef PRIM_H
#define PRIM_H

#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"

class Prim : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial) {
        this->grafo = g;
        this->initial = initial;
    }

    void run() {
        prim();
    }

    void prim();
    Vertice* popMenor();

private:
    int tempo;
    int initial;
    Grafo *grafo;
    QList<Vertice *> lista;

signals:
    void colorChanged();

};

#endif // PRIM_H

