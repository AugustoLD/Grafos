#ifndef TOPOLOGICA_H
#define TOPOLOGICA_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"

class Topologica : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial) {
        this->grafo = g;
        this->initial = initial;
    }
    void run() {
        ordenacaoTopologica();
    }

    void ordenacaoTopologica();
    void visit(Vertice *v);
    QList <Vertice *> getList (){   return lista;   }

private:
    int tempo;
    int initial;
    Grafo *grafo;
    QList<Vertice *> lista;

signals:
    void colorChanged();

};

#endif // TOPOLOGICA_H
