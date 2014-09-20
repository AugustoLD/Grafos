#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"
#include "aresta.h"

class FordFulkerson : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo *g, int source, int target) {
        this->g = g;
        this->source = source;
        this->target = target;
    }

    void run() {
        fordFulkerson();
    }

private:
    int source;
    int target;

    Grafo *g;
    void fordFulkerson();
    void findPath(QList<Aresta*> pathList, Vertice **V, Vertice *currentVertice);
    void calculateFlow(QList<Aresta*> pathList);

signals:
    void colorChanged();

};

#endif // FORDFULKERSON_H
