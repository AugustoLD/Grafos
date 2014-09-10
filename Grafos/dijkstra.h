#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"
#include "aresta.h"

#define INF 1000000

class Dijkstra : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial) {  this->g = g; this->initial = initial;}

    void run() {
        dijkstra();
    }

private:
    int tempo;
    int initial;
    Grafo *g;
    void dijkstra();

signals:
    void colorChanged();

};


#endif // DIJKSTRA_H
